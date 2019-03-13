from django.http import HttpResponse

def view1(request):
    return HttpResponse('hello1\n')

def view2(request):
    return HttpResponse('hello2\n')

def view3(request):
    return HttpResponse('hello3\n')
