from django.contrib import admin
from .models import UserProfile, Address, Banner, Product, Cart, Order, Comment, Announcement

@admin.register(Product)
class ProductAdmin(admin.ModelAdmin):
    list_display = ('name', 'price', 'seller', 'status', 'created_at')
    list_filter = ('status', 'created_at')
    search_fields = ('name', 'description', 'seller__username')
    actions = ['make_active']
    def make_active(self, request, queryset):
        updated = queryset.update(status='active')
        self.message_user(request, f"{updated} 个商品已审核通过并上架。")
    make_active.short_description = '审核通过（上架）所选商品'

@admin.register(Announcement)
class AnnouncementAdmin(admin.ModelAdmin):
    list_display = ('title', 'author', 'created_at')
    search_fields = ('title', 'content', 'author__username')
    list_filter = ('created_at',)

@admin.register(Banner)
class BannerAdmin(admin.ModelAdmin):
    list_display = ('id', 'image', 'link', 'order', 'is_active', 'created_at')
    list_filter = ('is_active',)
    search_fields = ('link',)

@admin.register(Order)
class OrderAdmin(admin.ModelAdmin):
    list_display = ('id', 'product', 'buyer', 'seller', 'amount', 'status', 'order_time')
    list_filter = ('status', 'order_time')
    search_fields = ('product__name', 'buyer__username', 'seller__username')

@admin.register(Comment)
class CommentAdmin(admin.ModelAdmin):
    list_display = ('id', 'product', 'user', 'content', 'parent', 'created_at')
    search_fields = ('content', 'user__username', 'product__name')
    list_filter = ('created_at',)

@admin.register(UserProfile)
class UserProfileAdmin(admin.ModelAdmin):
    list_display = ('user', 'nickname', 'contact', 'balance')
    search_fields = ('user__username', 'nickname', 'contact')

@admin.register(Address)
class AddressAdmin(admin.ModelAdmin):
    list_display = ('user', 'receiver', 'phone', 'detail')
    search_fields = ('user__username', 'receiver', 'phone', 'detail')

@admin.register(Cart)
class CartAdmin(admin.ModelAdmin):
    list_display = ('user', 'product', 'quantity', 'added_at')
    search_fields = ('user__username', 'product__name')
