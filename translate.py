import argparse

from googleapiclient.discovery import build

def translate_text(text, target_language):
    service = build('translate', 'v2', developerKey='AIzaSyDi6NOtgm4lOMDAAi1pwvNF4KwjjgQmOCw')
    translation = service.translations().list(source='en', target=target_language, q=text).execute()
    return translation['translations'][0]['translatedText']

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Translate text using Google Translate API.')
    parser.add_argument('--text', help='The text to translate.', required=True)
    parser.add_argument('--target-language', help='The target language code.', required=True)
    parser.add_argument('--api-key', help='Your Google Cloud API key.', required=True)
    args = parser.parse_args()

    print(translate_text(args.text, args.target_language, args.api_key))
