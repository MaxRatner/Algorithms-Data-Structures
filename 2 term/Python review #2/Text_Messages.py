def start(bot, update):
    text_start = 'Привет! \n' 'Команды бота - /help \n' \
                 'Введите ссылку на страницу с википедии, глубину поиска\n' \
                 'Пример:\n' 'https://ru.wikipedia.org/wiki/page123 10'
    bot.sendMessage(chat_id=update.message.chat_id, text=text_start)


def help(bot, update):
    text_top = 'Выводит топ самых часто или редко используемых слов:\n' \
               '/top N asc или /top N desc \n\n'
    text_stop_words = 'Выводит слова-выбросы:\n' '/stop_words \n\n'
    text_cloud = 'Нарисовать облако слов в указанной цветовой гамме:\n' '/word_cloud COLOR \n\n'
    text_describe = 'Вывести распределение частот слов и их длин:\n' '/describe \n\n'
    text_describe_word = 'выводит всю доступную статистику по данному слову в тексте:\n' \
                         '/describe WORD \n\n'
    bot.sendMessage(chat_id=update.message.chat_id,
                    text='{}{}{}{}{}'.format(text_top, text_stop_words,
                                             text_cloud, text_describe,
                                             text_describe_word))
