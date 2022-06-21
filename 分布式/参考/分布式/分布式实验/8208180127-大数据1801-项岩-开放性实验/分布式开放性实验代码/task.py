from workers import app
from bs4 import BeautifulSoup
from urllib.request import urlopen
from urllib.parse import urlparse
import re
import threading

def getInternalLinks(bs, includeUrl):
    includeUrl = '{}://{}'.format(urlparse(includeUrl).scheme, urlparse(includeUrl).netloc)
    internalLinks = []
    for link in bs.find_all('a', href=re.compile('^(/|.*'+includeUrl+')')):
        if link.attrs['href'] is not None:
            if link.attrs['href'] not in internalLinks:
                if(link.attrs['href'].startswith('/')):
                    internalLinks.append(includeUrl+link.attrs['href'])
                else:
                    internalLinks.append(link.attrs['href'])
    return internalLinks

def getExternalLinks(bs, excludeUrl):
    externalLinks = []
    for link in bs.find_all('a', href=re.compile('^(http|www)((?!'+excludeUrl+').)*$')):
        if link.attrs['href'] is not None:
            if link.attrs['href'] not in externalLinks:
                externalLinks.append(link.attrs['href'])
    return externalLinks

allExtLinks = set()
allIntLinks = set()
collectedLinks=set()
def getAllExternalLinks(siteUrl,q):
    html = urlopen(siteUrl,timeout=5)
    result=[siteUrl,html.info()['Content-Length']]
    q.append(result)
    domain = '{}://{}'.format(urlparse(siteUrl).scheme,
                              urlparse(siteUrl).netloc)
    bs = BeautifulSoup(html, 'html.parser')
    internalLinks = getInternalLinks(bs, domain)
    externalLinks = getExternalLinks(bs, domain)
    for link in internalLinks:
        if link not in allIntLinks:
            allIntLinks.add(link)
            #print("internalLink:{}".format(link))
    for link in externalLinks:
        if link not in allExtLinks:
            allExtLinks.add(link)
            html_e = urlopen(link,timeout=5)
            result_e = [link, html_e.info()['Content-Length']]
            q.append(result_e)
            #print("externalLink:{}".format(link))
    collectedLinks.add(siteUrl)

@app.task
def thread_crawling(url):
    thread_list=[]
    res=[]
    allIntLinks.add(url)
    while len(allIntLinks-collectedLinks)>0 and len(allIntLinks)<50:
        for url in allIntLinks:
            if url not in collectedLinks:
                t=threading.Thread(target=getAllExternalLinks,args=(url,res),)
                t.setDaemon(True)
                t.start()
                thread_list.append(t)
        for i in thread_list:
            i.join()
        #print(res)
    return dict(res)




