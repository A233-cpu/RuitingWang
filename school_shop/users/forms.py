from django import forms
from django.contrib.auth.models import User
from .models import UserProfile, Address, Comment, Product, ProductImage
from django.contrib.auth.forms import UserCreationForm, AuthenticationForm
from django.forms.widgets import ClearableFileInput
from django.contrib.auth.password_validation import validate_password

class UserRegisterForm(UserCreationForm):
    email = forms.EmailField(required=True)
    avatar = forms.ImageField(required=False)
    nickname = forms.CharField(max_length=30, required=False)
    contact = forms.CharField(max_length=100, required=False)

    class Meta:
        model = User
        fields = ['username', 'email', 'password1', 'password2']
    
    # 覆盖密码验证方法，不做任何验证
    def _post_clean(self):
        super(forms.ModelForm, self)._post_clean()
        # 清除密码验证错误
        self.fields['password1'].validators = []
        self.fields['password2'].validators = []
    
    def clean_password2(self):
        # 只检查两次密码是否一致，不做其他验证
        password1 = self.cleaned_data.get("password1")
        password2 = self.cleaned_data.get("password2")
        if password1 and password2 and password1 != password2:
            raise forms.ValidationError("密码不匹配，请确保两次输入的密码一致。")
        return password2

class UserLoginForm(AuthenticationForm):
    username = forms.CharField(label='用户名')
    password = forms.CharField(label='密码', widget=forms.PasswordInput)

class UserProfileForm(forms.ModelForm):
    class Meta:
        model = UserProfile
        fields = ['avatar', 'nickname', 'contact']

class AddressForm(forms.ModelForm):
    class Meta:
        model = Address
        fields = ['receiver', 'phone', 'detail']

class CommentForm(forms.ModelForm):
    class Meta:
        model = Comment
        fields = ['content']
        widgets = {
            'content': forms.Textarea(attrs={'rows': 2, 'placeholder': '说点什么...'}),
        }

class MultipleImageInput(ClearableFileInput):
    allow_multiple_selected = True
    input_type = 'file'

class ProductForm(forms.ModelForm):
    image = forms.ImageField(
        label='主图',
        required=True,
        help_text='选择商品的主要展示图片',
        error_messages={'required': '请上传商品主图'}
    )
    
    # 不在表单中定义这个字段，而是在视图中直接处理
    # extra_images字段由视图函数直接处理
    
    class Meta:
        model = Product
        fields = ['name', 'description', 'price', 'image', 'category']
        widgets = {
            'description': forms.Textarea(attrs={
                'rows': 4, 
                'placeholder': '请详细描述商品的使用情况、新旧程度、使用年限等信息...', 
                'class': 'form-control'
            }),
            'name': forms.TextInput(attrs={
                'placeholder': '请输入商品名称', 
                'class': 'form-control'
            }),
            'price': forms.NumberInput(attrs={
                'placeholder': '0.00', 
                'step': '0.01', 
                'class': 'form-control'
            }),
            'category': forms.Select(attrs={
                'class': 'form-control'
            }),
        }
        labels = {
            'name': '商品名称',
            'description': '商品描述',
            'price': '价格（元）',
            'category': '商品类别',
        }
        error_messages = {
            'name': {'required': '商品名称不能为空'},
            'description': {'required': '商品描述不能为空'},
            'price': {'required': '价格不能为空'},
            'category': {'required': '请选择商品类别'},
        } 