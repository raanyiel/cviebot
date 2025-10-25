import requests
from bs4 import BeautifulSoup
import time
import random

def scrape(url):
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36'
    }
    
    try:
        response = requests.get(url, headers=headers)
        response.raise_for_status()
        
        soup = BeautifulSoup(response.content, 'html.parser')
        
        posts = soup.find_all('li')
        
        full_urls = []
        for post in posts:
            if 'javascript-hide' in post.get('class', []):
                post.extract()
            a_tag = post.find('a', class_='directlink largeimg')
            if a_tag:
                full_url = a_tag.get('href')
                if full_url:
                    full_urls.append(full_url)
        
        if full_urls:
            random_url = random.choice(full_urls)
            print(f"{random_url}")
        
        return posts
        
    except requests.RequestException as e:
        print(f"Error fetching data: {e}")
        return None

if __name__ == "__main__":
    url = "https://yande.re/post?tags=gasai_yuno"
    time.sleep(1)
    posts = scrape(url)