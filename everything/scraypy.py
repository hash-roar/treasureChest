from bs4 import BeautifulSoup as bf
from urllib.request import urlopen
import re
import threading
from concurrent.futures import ThreadPoolExecutor 
from concurrent.futures import wait
# html = urlopen("https://www.zhihu.com/question/341311495")
# bf_obj = bf(html.read(),'html.parser')
# with open('pagezhihu','w') as f:
#     f.write(bf_obj.prettify())
#     print("success")
with open("./pagezhihu",'r') as f:
    bf_obj = bf(f.read(),'html.parser')

imgs = bf_obj.find_all("img")

urls = []
for img in imgs:
    if not re.match(r"^http.*",img["src"]):
        continue
    urls.append(img["src"])

# for img in imgs:
#     if not re.match(r"^http.*",img["src"]):
#         continue
#     urls.append(img['src'])

img_path_root = "D:\\download\\image\\表情包\\"

def  thread_scray (url,img_path_root):
    img_name = (url.split("/"))[-1].split("?")[0]
    img_path = img_path_root+img_name
    print(url)
    with open(img_path,"wb") as f:
        f.write(urlopen(url).read())
    return True

def download(urls,img_path_root):
    index = 0
    exexcutor  = ThreadPoolExecutor(max_workers=8)
    futuers = []
    for url in urls:
        futuers.append(exexcutor.submit(thread_scray,url,img_path_root)) 
        index+=1
    result = wait(futuers,timeout=None,return_when="ALL_COMPLETED")
    suceess = 0
    for suc in result.done:
        if suc.result(): suceess+=1
    print('下载结束,总数:'+str(len(urls))+'---->成功数:'+str(suceess)+'--->存放目录:'+img_path_root)

if __name__ == '__main__':
    download(urls,img_path_root)