import numpy
import os
import json
import matplotlib.pyplot as plt
from wordcloud import WordCloud
from operator import itemgetter


def cloud(bot, update):
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    color = update.message.text.split()[1]
    with open('{}/NotSrcFiles/ContentPage'.format(path), 'r') as file:
        text = file.read()
    cloud_of_words = WordCloud(colormap=color, background_color='white').generate(text)
    plt.imshow(cloud_of_words, interpolation='bilinear')
    cloud_of_words = WordCloud(max_font_size=40, colormap=color,
                               background_color='white').generate(text)
    plt.figure()
    plt.imshow(cloud_of_words, interpolation="bilinear")
    plt.axis("off")
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    path = '{}/NotSrcFiles/cloud.png'.format(path)
    plt.savefig(path, format='png')
    bot.send_photo(chat_id=update.message.chat_id, photo=open(path, 'rb'))
    plt.clf()


def f(a, b, c):
    return a < c < b


def stop_words(bot, update):
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    with open('{}/NotSrcFiles/DictMain'.format(path), 'r') as file:
        hist = json.load(file)
    intro = 'Слова - выбросы:'
    bot.sendMessage(chat_id=update.message.chat_id, text=intro)
    garbage_list = []
    for key in hist:
        garbage_list.append(hist[key])
    usual_deviation = numpy.std(garbage_list)
    medium_deviation = numpy.mean(garbage_list)
    dev_1 = medium_deviation - 3 * usual_deviation
    dev_2 = medium_deviation + 3 * usual_deviation
    for key in hist:
        frequency = hist[key]
        if not f(dev_1, dev_2, frequency):
            bot.sendMessage(chat_id=update.message.chat_id,
                            text='{}'.format(key))


def top_n(bot, update):
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    with open('{}/NotSrcFiles/DictMain'.format(path), 'r') as file:
        hist = json.load(file)
    top_numb = int(update.message.text.split()[1])
    top_freq = update.message.text.split()[2]
    sorted_list = sorted(hist.items(), key=itemgetter(1))
    top_list = []
    for key in hist:
        top_list.append(hist[key])
    usual_deviation = numpy.std(top_list)
    medium_deviation = numpy.mean(top_list)
    dev_1 = medium_deviation - 3 * usual_deviation
    dev_2 = medium_deviation + 3 * usual_deviation
    count_temp = 0
    if top_freq == 'asc':
        bot.sendMessage(chat_id=update.message.chat_id,
                        text='Топ самых частыо используемых слов:'.format(top_numb))
        for i in range(len(sorted_list) - 1, -1, -1):
            pair = sorted_list[i]
            if f(dev_1, dev_2, pair[1]) and count_temp < top_numb:
                bot.sendMessage(chat_id=update.message.chat_id,
                                text=pair[0])
                count_temp += 1
    if top_freq == 'desc':
        bot.sendMessage(chat_id=update.message.chat_id,
                        text='Топ самых редко используемых слов:'.format(top_numb))
        for i in range(0, len(sorted_list), 1):
            pair = sorted_list[i]
            if f(dev_1, dev_2, pair[1]) and count_temp < top_numb:
                bot.sendMessage(chat_id=update.message.chat_id,
                                text=pair[0])
                count_temp += 1
