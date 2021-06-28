from __future__ import unicode_literals

import logging
import os
import re
import time

from urllib.parse import urlparse

import pdfkit
import requests
from bs4 import BeautifulSoup as bf

html_template = """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
</head>
<body>
{content}
</body>
</html>
"""


class Crawler(object):
    name = None

    def __init__(self,name,start_url):
        self.name=name
        self.start_url = start_url
        self.domain = '{uri.scheme}://{uri.netloc}'.format(uri=urlparse(self.start_url))
    
    @staticmethod
    def request(url,**kwargs):
        response = requests.get(url,headers={'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.114 Safari/537.36'})

        print(response.status_code)
        return response
    def parse_menu(self,response):
        raise NotImplementedError
    
    def parse_body(self,response):
        raise NotImplementedError
    
    def run(self):
        start = time.time()
        options = {
            'page-size': 'Letter',
            'margin-top': '0.75in',
            'margin-right': '0.75in',
            'margin-bottom': '0.75in',
            'margin-left': '0.75in',
            'encoding': "UTF-8",
            'custom-header': [
                ('Accept-Encoding', 'gzip')
            ],
            'cookie': [
                ('cookie-name1', 'cookie-value1'),
                ('cookie-name2', 'cookie-value2'),
            ],
            'outline-depth': 10,
        }
        htmls=[]
        tam = self.request(self.start_url)
        print(tam.status_code)
        for index,url in enumerate(self.parse_menu(tam)):
            html =self.parse_body(self.request(url))
            f_name = ".".join([str(index),"html"])
            with open(f_name,'wb') as f:
                f.write(html)
            htmls.append(f_name)
        

        pdfkit.from_file(htmls,self.name+".pdf",options=options)
        for html in htmls:
            os.remove(html)
        total_time = time.time() - start
        print(u"总共耗时:%f 秒" % total_time)

class pythonTutor(Crawler):

    def parse_menu(self, response):
        print(response)
        soup = bf(response.content,"html.parser")
        menu_tag = soup.findAll(class_="uk-nav uk-nav-side")[1]
        for li in menu_tag.findAll("li"):
            url = li.a.gett("href")
            if not url.startwith("http"):
                url = "".join([self.domain,url])
            yield url
    
    def parse_body(self, response):
        
        try:
            soup = bf(response.content,"html.parser")
            body = soup.findAll(class_="x-wiki-content x-main-content")

            title = soup.find('h4').get_text()
            center_tag = soup.new_tag("center")
            title_tag = soup.new_tag('h1')
            title_tag.string = title
            center_tag.insert(1, title_tag)
            body.insert(1, center_tag)

            html = str(body)
            # body中的img标签的src相对路径的改成绝对路径
            pattern = "(<img .*?src=\")(.*?)(\")"

            def func(m):
                if not m.group(2).startswith("http"):
                    rtn = "".join([m.group(1), self.domain, m.group(2), m.group(3)])
                    return rtn
                else:
                    return "".join([m.group(1), m.group(2), m.group(3)])

            html = re.compile(pattern).sub(func, html)
            html = html_template.format(content=html)
            html = html.encode("utf-8")
            return html
        except Exception as e:
            logging.error("解析错误", exc_info=True)

if __name__ == '__main__':
    start_url = "http://www.liaoxuefeng.com/wiki/0013739516305929606dd18361248578c67b8067c8c017b000"
    crawler = pythonTutor("廖雪峰Git", start_url)
    crawler.run()