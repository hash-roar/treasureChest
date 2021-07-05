import requests
import sys
import io

sys.stdout = io.TextIOWrapper(sys.stdout.buffer,encoding='utf8')
#改变标准输出的默认编码

url = 'url'

#在浏览器中复制得到cookie
cookie_str = r'JSESSIONID=; 
iPlanetDirectoryPro=

#把cookie字符串处理成字典，以便接下来使用
cookies = {}
for line in cookie_str.split(';'):
    key, value = line.split('=', 1)
    cookies[key] = value
#设置请求头
headers = {'User-agent':' '}

#在发送get请求时带上请求头和cookies
resp = requests.get(url, headers = headers, cookies = cookies)

print(resp.content.decode('utf-8'))