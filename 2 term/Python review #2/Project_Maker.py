import urllib.request
import re
import json
import os
from bs4 import BeautifulSoup


def dict_next(words, hist):
    for i in range(0, len(words) - 1, 1):
        current = words[i]
        next = words[i + 1]
        if current == 'страница' or current == 'отсутствует'\
                or next == 'страница' or next == 'отсутствует':
            continue
        if current in hist:
            if next in hist[current]:
                hist[current][next] += 1
            else:
                hist[current][next] = 1
        else:
            hist[current] = {}
            hist[current][next] = 1


def dict_prev(words, hist):
    for i in range(0, len(words) - 1, 1):
        current = words[i]
        next = words[i + 1]
        if current == 'страница' or current == 'отсутствует'\
                or next == 'страница' or next == 'отсутствует':
            continue
        if next in hist:
            if current in hist[next]:
                hist[next][current] += 1
            else:
                hist[next][current] = 1
        else:
            hist[next] = {}
            hist[next][current] = 1


def dict_main(words, hist):
    for i in range(0, len(words), 1):
        current = words[i]
        if current == 'страница' or current == 'отсутствует':
            continue
        if current in hist:
            hist[current] += 1
        else:
            hist[current] = 1


def html_get(url):

    response = urllib.request.urlopen(url)
    return response.read()


def html_parse(html, hist_next, hist_prev, hist_main, used_links):
    soup = BeautifulSoup(html, 'html.parser')
    main_part = soup.find('div', class_='mw-parser-output')
    paragraphs = main_part.find_all('p')
    s = str(paragraphs).lower()
    s = s.replace('>', ' ')
    s = s.replace('<', ' ')
    reg = re.compile('[^а-яА-Я ]')
    s = reg.sub('', s)
    s = re.sub(r'\s+', ' ', s)
    s = s.replace('страница', '')
    s = s.replace('отсутствует', '')
    path = os.getcwd()
    path = path.replace('ParsingPage', '')
    with open('{}/NotSrcFiles/ContentPage'.format(path), 'a') as file:
        file.write(s)
    words = s.split(' ')
    dict_next(words, hist_next)
    dict_prev(words, hist_prev)
    dict_main(words, hist_main)
    links = []
    tag_links = soup.find_all('a')
    for tag in tag_links:
        link = str(tag.get('href'))
        if link[0:6] == '/wiki/' and link[-3:] != '/ru' and link not in used_links:
            links.append('https://ru.wikipedia.org{}'.format(link))
            used_links.add('https://ru.wikipedia.org{}'.format(link))
    return links


def get_message(bot, update):
    path = os.getcwd()
    path = path.replace('ParsingPage', '')
    with open('{}/NotSrcFiles/DictNext'.format(path), 'w') as file:
        pass
    with open('{}/NotSrcFiles/DictPrev'.format(path), 'w') as file:
        pass
    with open('{}/NotSrcFiles/DictMain'.format(path), 'w') as file:
        pass
    with open('{}/NotSrcFiles/ContentPage'.format(path), 'w') as file:
        pass
    url = update.message.text.split()[0]
    depth = update.message.text.split()[1]
    hist_next = {}
    hist_prev = {}
    hist_main = {}
    links = [url]
    used_links = set(url)
    for i in range(0, int(depth), 1):
        new_links = []
        for link in links:
            html = get_html(link)
            parse_result = parse_html(html, hist_next, hist_prev, hist_main, used_links)
            new_links.extend(parse_result)
        links = new_links
    with open('{}/NotSrcFiles/DictNext'.format(path), 'w') as file:
        json.dump(hist_next, file)
    with open('{}/NotSrcFiles/DictPrev'.format(path), 'w') as file:
        json.dump(hist_prev, file)
    with open('{}/NotSrcFiles/DictMain'.format(path), 'w') as file:
        json.dump(hist_main, file)
