from django.db import models
from django.contrib.auth.models import User

# Create your models here.

class UserProfile(models.Model):
    user = models.OneToOneField(User, on_delete=models.CASCADE, related_name='profile')
    avatar = models.ImageField(upload_to='avatars/', blank=True, null=True, verbose_name='头像')
    nickname = models.CharField(max_length=30, blank=True, verbose_name='昵称')
    contact = models.CharField(max_length=100, blank=True, verbose_name='联系方式')
    balance = models.DecimalField(max_digits=10, decimal_places=2, default=0, verbose_name='账户余额')
    
    def __str__(self):
        return self.nickname or self.user.username

class Address(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name='addresses')
    receiver = models.CharField(max_length=30, verbose_name='收货人')
    phone = models.CharField(max_length=20, verbose_name='电话')
    detail = models.CharField(max_length=255, verbose_name='地址详情')
    
    def __str__(self):
        return f'{self.receiver} - {self.detail}'

class Banner(models.Model):
    image = models.ImageField(upload_to='banners/', verbose_name='图片')
    link = models.URLField(blank=True, null=True, verbose_name='链接')
    order = models.PositiveIntegerField(default=0, verbose_name='排序')
    is_active = models.BooleanField(default=True, verbose_name='状态')
    created_at = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

    class Meta:
        ordering = ['order', '-created_at']

    def __str__(self):
        return f"Banner {self.id}"

class Product(models.Model):
    STATUS_CHOICES = [
        ('pending', '待审核'),
        ('active', '已上架'),
        ('inactive', '已下架'),
    ]
    
    CATEGORY_CHOICES = [
        ('books', '教材书籍'),
        ('digital', '数码产品'),
        ('clothes', '服装鞋包'),
        ('daily', '日常用品'),
        ('sports', '运动健身'),
        ('others', '其他分类'),
    ]
    
    name = models.CharField(max_length=100, verbose_name='名称')
    description = models.TextField(verbose_name='描述')
    image = models.ImageField(upload_to='products/', verbose_name='图片')
    price = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='价格')
    seller = models.ForeignKey(User, on_delete=models.CASCADE, related_name='products', verbose_name='发布用户')
    status = models.CharField(max_length=10, choices=STATUS_CHOICES, default='pending', verbose_name='状态')
    category = models.CharField(max_length=20, choices=CATEGORY_CHOICES, default='others', verbose_name='商品类别')
    created_at = models.DateTimeField(auto_now_add=True, verbose_name='发布时间')

    def __str__(self):
        return self.name

class ProductImage(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE, related_name='images', verbose_name='商品')
    image = models.ImageField(upload_to='products/', verbose_name='图片')
    uploaded_at = models.DateTimeField(auto_now_add=True, verbose_name='上传时间')
    def __str__(self):
        return f"{self.product.name} 图片"

class Cart(models.Model):
    user = models.ForeignKey(User, on_delete=models.CASCADE, related_name='cart_items', verbose_name='用户')
    product = models.ForeignKey(Product, on_delete=models.CASCADE, verbose_name='商品')
    quantity = models.PositiveIntegerField(default=1, verbose_name='数量')
    added_at = models.DateTimeField(auto_now_add=True, verbose_name='加入时间')

    class Meta:
        unique_together = ('user', 'product')

    def __str__(self):
        return f"{self.user.username} - {self.product.name} x {self.quantity}"

class Order(models.Model):
    STATUS_CHOICES = [
        ('paid', '已支付'),
        ('completed', '已完成'),
        ('cancelled', '已取消'),
    ]
    buyer = models.ForeignKey(User, on_delete=models.CASCADE, related_name='orders_bought', verbose_name='买家')
    seller = models.ForeignKey(User, on_delete=models.CASCADE, related_name='orders_sold', verbose_name='卖家')
    product = models.ForeignKey(Product, on_delete=models.CASCADE, verbose_name='商品')
    amount = models.DecimalField(max_digits=10, decimal_places=2, verbose_name='金额')
    order_time = models.DateTimeField(auto_now_add=True, verbose_name='下单时间')
    status = models.CharField(max_length=10, choices=STATUS_CHOICES, default='paid', verbose_name='状态')

    def __str__(self):
        return f"订单#{self.id} - {self.product.name}"

class Comment(models.Model):
    product = models.ForeignKey(Product, on_delete=models.CASCADE, related_name='comments', verbose_name='商品')
    user = models.ForeignKey(User, on_delete=models.CASCADE, verbose_name='用户')
    content = models.TextField(verbose_name='内容')
    parent = models.ForeignKey('self', null=True, blank=True, on_delete=models.CASCADE, related_name='replies', verbose_name='父评论')
    created_at = models.DateTimeField(auto_now_add=True, verbose_name='创建时间')

    def __str__(self):
        return f"{self.user.username}: {self.content[:20]}"

class Announcement(models.Model):
    title = models.CharField(max_length=100, verbose_name='标题')
    content = models.TextField(verbose_name='内容')
    created_at = models.DateTimeField(auto_now_add=True, verbose_name='发布时间')
    author = models.ForeignKey(User, on_delete=models.SET_NULL, null=True, blank=True, verbose_name='发布人')

    def __str__(self):
        return self.title
