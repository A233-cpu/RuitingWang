from django import template
register = template.Library()

@register.filter
def get_item(dictionary, key):
    return dictionary.get(key, '')

@register.filter
def filter_products(products, status):
    """
    根据状态筛选产品列表
    用法：{{ products|filter_products:'active' }}
    """
    return [product for product in products if product.status == status] 