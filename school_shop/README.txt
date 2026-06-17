Python_Django项目
(1)创建了templates目录
（2）
创建成功后自带文件
manage.py		项目的管理、启动项目、创建app、数据库管理
_init_.py
settings.py		项目配置（连接数据库mysql）
urls.py			url和函数对应关系
asgi.py			接收网络请求（不需动）
wsgi.py			接收网络请求（不需动）

1.campus_market
(1)templates
base.html: HTML 文件是校园二手交易平台的基础模板，实现了用户认证、导航、全局提示等核心功能，基于 Django 和 Bootstrap 构建，具备响应式布局和基本的交互逻辑.
home.html:home.html 是校园二手交易平台的核心页面，通过清晰的分类导航、视觉突出的轮播图和响应式商品列表，引导用户高效浏览和搜索商品.

2.创建app users//需要再settings中注册
apps.py			app启动类
migrations		数据库变更记录
tests			固定不用动
admin.py		Django后台提供admin后台管理
views.py			函数的定义（视图函数）与url中函数对应
models.py		对数据库进行操作

media文件夹（图片）
avatars 设置头像
banners 横幅广告
bj  背景图
products 产品图


启动项目：
1. 启动开发服务器：
   python manage.py runserver
2. 访问 http://127.0.0.1:8000/
管理员界面：http://127.0.0.1:8000/admin      账号：admin,密码：123456
进入数据库连接工具，将school_shop.sql导入你的数据库中