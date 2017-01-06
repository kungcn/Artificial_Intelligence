from bs4 import BeautifulSoup

import urllib

inputUrl = raw_input("Please input the url you want to start:")
resultUrl = raw_input("Please input the url you want to search:")
seachUrlTimes = input("Please input the websites you allow to search:")

print "Start:"
print inputUrl
print "End:"
print resultUrl
print "Search Times:"
print seachUrlTimes

def recursive(url, times, result):
    html = urllib.urlopen(url).read()
    soup = BeautifulSoup(html)
    arrays = soup.findAll('a')
    for index in arrays:
        if index['href'] != "#" and len(arrays) > 0:
            url = index['href']
            print url
            if index['href'] == result:
                print index['href']
                return

            times = times - 1
            print times

            if times == 0 :
                print "No Answer"
                return

            recursive(url, times, result)

recursive(inputUrl, seachUrlTimes, resultUrl)