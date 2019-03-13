from django.urls import path
from . import views

urlpatterns = [
    path('view1', views.view1),
    path('view2/', views.view2),
    path('/view3', views.view3) # Leading slash not required; see below

    # ?: (urls.W002) Your URL pattern '/view3' has a route beginning
    # with a '/'. Remove this slash as it is unnecessary. If this
    # pattern is targeted in an include(), ensure the include() pattern
    # has a trailing '/'.
]
