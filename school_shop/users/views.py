from django.shortcuts import render, redirect, get_object_or_404
from django.contrib.auth import authenticate, login, logout
from django.contrib.auth.decorators import login_required
from django.contrib import messages
from django.urls import reverse
from .forms import UserRegisterForm, UserLoginForm, UserProfileForm, AddressForm, CommentForm, ProductForm
from .models import UserProfile, Address, Product, Cart, Order, Comment, Announcement, ProductImage
from django.contrib.auth.models import User
from django.http import JsonResponse, HttpResponseRedirect, Http404
from django.db import transaction
from django.db.models import Sum

# Create your views here.

# 用户注册
def register_view(request):
    if request.method == 'POST':
        form = UserRegisterForm(request.POST, request.FILES)
        if form.is_valid():
            user = form.save()
            # 创建用户扩展信息
            UserProfile.objects.create(
                user=user,
                avatar=form.cleaned_data.get('avatar'),
                nickname=form.cleaned_data.get('nickname'),
                contact=form.cleaned_data.get('contact')
            )
            messages.success(request, '注册成功，请登录！')
            return redirect('users:login')
    else:
        form = UserRegisterForm()
    return render(request, 'users/register.html', {'form': form})

# 用户登录
from django.contrib.auth.views import LoginView, LogoutView

class CustomLoginView(LoginView):
    template_name = 'users/login.html'
    authentication_form = UserLoginForm

class CustomLogoutView(LogoutView):
    next_page = '/'
    http_method_names = ['get', 'post', 'head', 'options']
    def get(self, request, *args, **kwargs):
        return self.post(request, *args, **kwargs)

# 个人信息展示与编辑
@login_required
def profile_view(request):
    # 自动为没有profile的用户创建profile
    profile, created = UserProfile.objects.get_or_create(user=request.user)
    if request.method == 'POST':
        form = UserProfileForm(request.POST, request.FILES, instance=profile)
        if form.is_valid():
            form.save()
            messages.success(request, '个人信息已更新！')
            return redirect('users:profile')
    else:
        form = UserProfileForm(instance=profile)
    return render(request, 'users/profile.html', {'form': form, 'profile': profile})

# 地址管理（列表、新增、编辑、删除）
@login_required
def address_list(request):
    addresses = request.user.addresses.all()
    return render(request, 'users/address_list.html', {'addresses': addresses})

@login_required
def address_add(request):
    if request.method == 'POST':
        form = AddressForm(request.POST)
        if form.is_valid():
            address = form.save(commit=False)
            address.user = request.user
            address.save()
            messages.success(request, '地址添加成功！')
            return redirect('users:address_list')
    else:
        form = AddressForm()
    return render(request, 'users/address_form.html', {'form': form})

@login_required
def address_edit(request, pk):
    address = get_object_or_404(Address, pk=pk, user=request.user)
    if request.method == 'POST':
        form = AddressForm(request.POST, instance=address)
        if form.is_valid():
            form.save()
            messages.success(request, '地址更新成功！')
            return redirect('users:address_list')
    else:
        form = AddressForm(instance=address)
    return render(request, 'users/address_form.html', {'form': form})

@login_required
def address_delete(request, pk):
    address = get_object_or_404(Address, pk=pk, user=request.user)
    if request.method == 'POST':
        address.delete()
        messages.success(request, '地址已删除！')
        return redirect('users:address_list')
    return render(request, 'users/address_confirm_delete.html', {'address': address})

def product_detail(request, pk):
    product = get_object_or_404(Product, pk=pk)
    # 只有上架商品或本人可见
    if product.status != 'active' and (not request.user.is_authenticated or request.user != product.seller):
        raise Http404("No Product matches the given query.")
    comments = product.comments.filter(parent__isnull=True).select_related('user').prefetch_related('replies')
    comment_form = CommentForm()
    return render(request, 'users/product_detail.html', {
        'product': product,
        'comments': comments,
        'comment_form': comment_form,
    })

@login_required
def cart_add(request, pk):
    product = get_object_or_404(Product, pk=pk, status='active')
    exists = Cart.objects.filter(user=request.user, product=product).exists()
    if exists:
        messages.info(request, '该商品已在购物车中，无需重复添加。')
        return HttpResponseRedirect(request.META.get('HTTP_REFERER', '/'))
    Cart.objects.create(user=request.user, product=product)
    messages.success(request, '商品已加入购物车！')
    return HttpResponseRedirect(request.META.get('HTTP_REFERER', '/'))

@login_required
def cart_view(request):
    cart_items = Cart.objects.filter(user=request.user).select_related('product')
    total = sum(item.product.price * item.quantity for item in cart_items)
    return render(request, 'users/cart.html', {'cart_items': cart_items, 'total': total})

@login_required
def cart_remove(request, pk):
    cart_item = get_object_or_404(Cart, pk=pk, user=request.user)
    cart_item.delete()
    return HttpResponseRedirect(request.META.get('HTTP_REFERER', '/users/cart/'))

@login_required
def buy_product(request, pk):
    product = get_object_or_404(Product, pk=pk)
    if product.status != 'active':
        messages.error(request, '该商品已下架，无法购买。')
        return redirect('users:product_detail', pk=pk)
    if request.method == 'POST':
        if product.seller == request.user:
            messages.error(request, '不能购买自己发布的商品！')
            return redirect('users:product_detail', pk=pk)
        with transaction.atomic():
            order = Order.objects.create(
                buyer=request.user,
                seller=product.seller,
                product=product,
                amount=product.price,
                status='paid',
            )
            # 卖家余额增加，确保有profile
            seller_profile, _ = UserProfile.objects.get_or_create(user=product.seller)
            seller_profile.balance += product.price
            seller_profile.save()
            # 商品下架
            product.status = 'inactive'
            product.save()
        messages.success(request, '购买成功，订单已生成！')
        return redirect('users:order_detail', pk=order.pk)
    return redirect('users:product_detail', pk=pk)

@login_required
def order_detail(request, pk):
    order = get_object_or_404(Order, pk=pk)
    if order.buyer != request.user and order.seller != request.user:
        return redirect('home')
    return render(request, 'users/order_detail.html', {'order': order})

@login_required
def my_orders(request):
    orders = Order.objects.filter(buyer=request.user).select_related('product', 'seller').order_by('-order_time')
    return render(request, 'users/my_orders.html', {'orders': orders})

@login_required
def sold_orders(request):
    orders = Order.objects.filter(seller=request.user).select_related('product', 'buyer').order_by('-order_time')
    return render(request, 'users/sold_orders.html', {'orders': orders})

@login_required
def comment_add(request, product_pk, parent_pk=None):
    product = get_object_or_404(Product, pk=product_pk, status='active')
    parent = None
    if parent_pk:
        parent = get_object_or_404(Comment, pk=parent_pk, product=product)
    if request.method == 'POST':
        form = CommentForm(request.POST)
        if form.is_valid():
            comment = form.save(commit=False)
            comment.product = product
            comment.user = request.user
            comment.parent = parent
            comment.save()
            return redirect('users:product_detail', pk=product_pk)
    return redirect('users:product_detail', pk=product_pk)

def announcement_list(request):
    announcements = Announcement.objects.order_by('-created_at')
    return render(request, 'users/announcement_list.html', {'announcements': announcements})

def announcement_detail(request, pk):
    announcement = get_object_or_404(Announcement, pk=pk)
    return render(request, 'users/announcement_detail.html', {'announcement': announcement})

@login_required
def product_create(request):
    if request.method == 'POST':
        # 打印请求中的文件数据以便调试
        print("POST数据:", request.POST)
        print("FILES内容:", request.FILES)
        print("FILES的keys:", request.FILES.keys())
        
        # 手动构建表单，确保正确处理文件上传
        form_data = request.POST.copy()
        form = ProductForm(form_data, request.FILES)
        
        # 强制跳过表单中extra_images字段的验证
        form.errors.pop('extra_images', None)
        
        # 手动检查必填字段
        has_errors = False
        if not form_data.get('name'):
            form.add_error('name', '商品名称不能为空')
            has_errors = True
        if not form_data.get('description'):
            form.add_error('description', '商品描述不能为空')
            has_errors = True
        if not form_data.get('price'):
            form.add_error('price', '价格不能为空')
            has_errors = True
        if not form_data.get('category'):
            form.add_error('category', '请选择商品类别')
            has_errors = True
            
        # 检查是否有主图上传
        if 'image' not in request.FILES:
            form.add_error('image', '请上传商品主图')
            has_errors = True
            
        # 如果没有错误或者只有extra_images字段的错误，则继续处理
        if form.is_valid() or (not has_errors and list(form.errors.keys()) == ['extra_images']):
            try:
                # 手动创建产品
                product = Product(
                    name=form_data.get('name'),
                    description=form_data.get('description'),
                    price=form_data.get('price'),
                    image=request.FILES.get('image'),
                    category=form_data.get('category', 'others'),  # 设置默认类别
                    seller=request.user,
                    status='active'
                )
                product.save()
                
                # 直接从request.FILES获取额外图片，而不是从表单
                extra_images = request.FILES.getlist('extra_images')
                print(f"找到的额外图片数量: {len(extra_images)}")  # 调试信息
                
                # 限制最多上传8张额外图片
                max_extra_images = 8
                count = 0
                for i, img in enumerate(extra_images):
                    if i >= max_extra_images:
                        break
                    try:
                        print(f"处理额外图片 {i+1}: {img.name}, 大小: {img.size}")
                        # 创建额外图片记录
                        ProductImage.objects.create(
                            product=product,
                            image=img
                        )
                        count += 1
                        print(f"已保存额外图片: {img.name}")
                    except Exception as e:
                        print(f"保存第{i+1}张额外图片时出错: {str(e)}")
                        # 继续处理下一张图片，不中断流程
                
                print(f"成功保存了 {count} 张额外图片")  # 调试信息
                messages.success(request, f'商品发布成功，已上架！共上传了{count}张额外图片。')
                return redirect('users:my_products')
                
            except Exception as e:
                print(f"产品创建过程中出错: {str(e)}")
                messages.error(request, f'商品发布失败: {str(e)}')
                # 如果出错，回到表单页面
                return render(request, 'users/product_form.html', {'form': form})
        else:
            print(f"表单验证错误: {form.errors}")
            for field, errors in form.errors.items():
                for error in errors:
                    print(f"字段 {field} 错误: {error}")
                    messages.error(request, f'字段 {field}: {error}')
    else:
        # 从URL参数获取类别
        category = request.GET.get('category', '')
        initial_data = {}
        if category:
            initial_data['category'] = category
        
        form = ProductForm(initial=initial_data)
    
    # 获取所有类别信息传递给模板
    categories = Product.CATEGORY_CHOICES
    
    return render(request, 'users/product_form.html', {
        'form': form,
        'categories': categories
    })

@login_required
def my_products(request):
    products = Product.objects.filter(seller=request.user).order_by('-created_at')
    # 统计每个商品的收益
    product_earnings = {}
    for product in products:
        earning = Order.objects.filter(product=product, status__in=['paid', 'completed']).aggregate(total=Sum('amount'))['total'] or 0
        product_earnings[product.pk] = earning
    # 统计总收益
    total_earning = Order.objects.filter(product__seller=request.user, status__in=['paid', 'completed']).aggregate(total=Sum('amount'))['total'] or 0
    return render(request, 'users/my_products.html', {'products': products, 'product_earnings': product_earnings, 'total_earning': total_earning})

@login_required
def product_toggle_status(request, pk):
    product = get_object_or_404(Product, pk=pk, seller=request.user)
    if product.status == 'active':
        product.status = 'inactive'
        messages.success(request, '商品已下架！')
    elif product.status == 'inactive':
        product.status = 'active'
        messages.success(request, '商品已重新上架！')
    product.save()
    return redirect('users:my_products')

@login_required
def product_delete(request, pk):
    product = get_object_or_404(Product, pk=pk, seller=request.user, status='inactive')
    if request.method == 'POST':
        product.delete()
        messages.success(request, '商品已删除！')
        return redirect('users:my_products')
    return render(request, 'users/product_confirm_delete.html', {'product': product})

@login_required
def cart_checkout(request):
    if request.method == 'POST':
        cart_ids = request.POST.getlist('cart_ids')
        if not cart_ids:
            messages.error(request, '请至少选择一个商品结算！')
            return redirect('users:cart')
        cart_items = Cart.objects.filter(id__in=cart_ids, user=request.user).select_related('product')
        order_ids = []
        with transaction.atomic():
            for item in cart_items:
                product = item.product
                if product.status != 'active':
                    continue  # 跳过已下架商品
                if product.seller == request.user:
                    continue  # 跳过自己发布的商品
                order = Order.objects.create(
                    buyer=request.user,
                    seller=product.seller,
                    product=product,
                    amount=product.price * item.quantity,
                    status='paid',
                )
                # 卖家余额增加
                seller_profile, _ = UserProfile.objects.get_or_create(user=product.seller)
                seller_profile.balance += product.price * item.quantity
                seller_profile.save()
                # 商品下架
                product.status = 'inactive'
                product.save()
                # 移除购物车项
                item.delete()
                order_ids.append(order.id)
        if order_ids:
            messages.success(request, f'成功结算 {len(order_ids)} 个商品，订单已生成！')
            # 跳转到第一个订单详情页
            return redirect('users:order_detail', pk=order_ids[0])
        else:
            messages.error(request, '没有可结算的商品（可能已下架或为自己商品）')
            return redirect('users:cart')
    return redirect('users:cart')
