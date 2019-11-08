import logging
from Text_Messages import help, start
from Top_Words import top_n, cloud, stop_words
from Describe_Words import describe, describe_word, describe_frequency, describe_length
from Project_Maker import get_message
from telegram.ext import Updater, CommandHandler, MessageHandler, Filters


def main():
    logging.basicConfig(format='%(asctime)s - %(name)s - %(levelname)s - %(message)s',
                        level=logging.INFO)
    logger = logging.getLogger(__name__)
    token = '600551393:AAGbKs6W3v_Ufw-G7xPK-gUfzLmDUZywd0E'
    updater = Updater(token=token)
    dispatcher = updater.dispatcher
    dispatcher.add_handler(MessageHandler(Filters.text, build_json))
    dispatcher.add_handler(CommandHandler('start', start))
    dispatcher.add_handler(CommandHandler('help', help))
    dispatcher.add_handler(CommandHandler('stop_words', stop_words))
    dispatcher.add_handler(CommandHandler('top', top_n))
    dispatcher.add_handler(CommandHandler('word_cloud', word_cloud))
    dispatcher.add_handler(CommandHandler('describe', describe))
    dispatcher.add_handler(CommandHandler('describe_word', describe_word))
    updater.start_polling()
    updater.idle()


if __name__ == '__main__':
    main()
