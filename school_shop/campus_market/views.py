from django.shortcuts import render, redirect
from django.contrib.auth.decorators import login_required
from users.models import Banner, Product

def home_view(request):
    banners = Banner.objects.filter(is_active=True).order_by('order', '-created_at')
    query = request.GET.get('q', '')
    category = request.GET.get('category', '')
    
    products = Product.objects.filter(status='active')
    
    if query:
        products = products.filter(name__icontains=query)
        
    if category:
        products = products.filter(category=category)
        
    products = products.order_by('-created_at')
    
    # 获取所有的类别选项
    categories = dict(Product.CATEGORY_CHOICES)
    
    return render(request, 'home.html', {
        'banners': banners, 
        'products': products, 
        'query': query,
        'current_category': category,
        'categories': categories
    }) 