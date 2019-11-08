import json
import numpy
import matplotlib.pyplot as plt
import os


def describe_word(bot, update):
    word = update.message.text.split()[1]
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    with open('{}/NotSrcFiles/DictMain'.format(path), 'r') as file:
        hist_main = json.load(file)
    with open('{}/NotSrcFiles/DictNext'.format(path), 'r') as file:
        hist_next = json.load(file)
    with open('{}/NotSrcFiles/DictPrev'.format(path), 'r') as file:
        hist_prev = json.load(file)
    if word not in hist_main:
        not_in_text = 'Данного слова не нашлось в статьях'
        bot.sendMessage(chat_id=update.message.chat_id, text=not_in_text)
        return
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='Слово встречается в тексте {} раз'.format(str(hist_main[word])))
    list_of_frequency = []
    for key in hist_main:
        list_of_frequency.append(hist_main[key])
    average_deviation = numpy.mean(list_of_frequency)
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='Средняя частота по всем словам - {}'.format(average_deviation))
    diff = abs(average_deviation - hist_main[word])
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='Отклонение от средней частоты - {}'.format(diff))
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='Слова, встречающиеся после него:')
    for next_word in hist_next[word]:
        bot.sendMessage(chat_id=update.message.chat_id,
                        text='{}'.format(next_word))
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='Слова, встречающиеся перед ним:')
    for prev_word in hist_prev[word]:
        bot.sendMessage(chat_id=update.message.chat_id,
                        text='{}'.format(prev_word))


def f(a, b, c):
    return a < c < b


def describe_frequency(bot, update, hist):
    list_of_frequency = []
    for key in hist:
        list_of_frequency.append(hist[key])
    usual_deviation = numpy.std(list_of_frequency)
    medium_deviation = numpy.mean(list_of_frequency)
    hist_of_frequency = {}
    for key in hist:
        frequency = hist[key]
        a = medium_deviation - 3 * usual_deviation
        b = medium_deviation + 3 * usual_deviation
        if f(a, b, frequency):
            if frequency in hist_of_frequency:
                hist_of_frequency[frequency] += 1
            else:
                hist_of_frequency[frequency] = 1
    intro = 'Распределение частот слов:'
    bot.sendMessage(chat_id=update.message.chat_id, text=intro)
    temp_hist = sorted(hist_of_frequency)
    a, b = [], []
    for key in temp_hist:
        if key != 1:
            a.append(key)
            b.append(hist_of_frequency[key])
    plt.axis([0.0, 15.0, 0.0, 500.0])
    plt.xlabel(u'Частота слова')
    plt.ylabel(u'Количество слов с такой частотой:')
    plt.grid()
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    path = '{}/NotSrcFiles/frequency.png'.format(path)
    plt.savefig(path, format='png')
    bot.send_photo(chat_id=update.message.chat_id, photo=open(path, 'rb'))
    plt.clf()


def describe_length(bot, update, hist):
    hist_of_length = {}
    for key in hist:
        length = len(key)
        if length in hist_of_length:
            hist_of_length[length] += hist[key]
        else:
            hist_of_length[length] = hist[key]
    temp_hist = sorted(hist_of_length)
    a, b = [], []
    for key in temp_hist:
        a.append(key)
        b.append(hist_of_length[key])
    intro = 'Распределение длин слов:'
    bot.sendMessage(chat_id=update.message.chat_id, text=intro)
    plt.axis([0.0, 20.0, 0.0, 500.0])
    plt.xlabel(u'Длина слова')
    plt.ylabel(u'Количество слов с такой длиной:')
    plt.grid()
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    path = '{}/NotSrcFiles/length.png'.format(path)
    plt.savefig(path, format='png')
    bot.send_photo(chat_id=update.message.chat_id, photo=open(path, 'rb'))
    plt.clf()


def describe(bot, update):
    if update.message.text != '/describe':
        describe_word(bot, update)
        return
    path = os.getcwd()
    path = path.replace('BaseCommands', '')
    with open('{}/NotSrcFiles/DictMain'.format(path), 'r') as file:
        hist = json.load(file)
    describe_frequency(bot, update, hist)
    describe_length(bot, update, hist)
