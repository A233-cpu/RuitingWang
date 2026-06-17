from django.urls import path
from . import views

app_name = 'users'

urlpatterns = [
    path('register/', views.register_view, name='register'),
    path('login/', views.CustomLoginView.as_view(), name='login'),
    path('logout/', views.CustomLogoutView.as_view(), name='logout'),
    path('profile/', views.profile_view, name='profile'),
    path('addresses/', views.address_list, name='address_list'),
    path('addresses/add/', views.address_add, name='address_add'),
    path('addresses/<int:pk>/edit/', views.address_edit, name='address_edit'),
    path('addresses/<int:pk>/delete/', views.address_delete, name='address_delete'),
    path('product/<int:pk>/', views.product_detail, name='product_detail'),
    path('product/<int:pk>/add_to_cart/', views.cart_add, name='cart_add'),
    path('cart/', views.cart_view, name='cart'),
    path('cart/add/<int:pk>/', views.cart_add, name='cart_add'),
    path('cart/remove/<int:pk>/', views.cart_remove, name='cart_remove'),
    path('product/<int:pk>/buy/', views.buy_product, name='buy_product'),
    path('order/<int:pk>/', views.order_detail, name='order_detail'),
    path('orders/', views.my_orders, name='my_orders'),
    path('orders/sold/', views.sold_orders, name='sold_orders'),
    path('product/<int:product_pk>/comment/', views.comment_add, name='comment_add'),
    path('product/<int:product_pk>/comment/<int:parent_pk>/', views.comment_add, name='comment_reply'),
    path('announcements/', views.announcement_list, name='announcement_list'),
    path('announcements/<int:pk>/', views.announcement_detail, name='announcement_detail'),
    path('products/create/', views.product_create, name='product_create'),
    path('products/mine/', views.my_products, name='my_products'),
    path('product/<int:pk>/toggle_status/', views.product_toggle_status, name='product_toggle_status'),
    path('product/<int:pk>/delete/', views.product_delete, name='product_delete'),
    path('cart/checkout/', views.cart_checkout, name='cart_checkout'),
] 