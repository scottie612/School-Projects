

from pymongo import MongoClient
from selenium import webdriver
from selenium_stealth import stealth
from selenium.webdriver.common.by import By
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
import time



chrome_options = webdriver.ChromeOptions()
chrome_options.add_argument("start-maximized")
chrome_options.add_argument("--headless")
chrome_options.add_argument('--log-level=3')
chrome_options.add_experimental_option("excludeSwitches", ["enable-automation"])
chrome_options.add_experimental_option('useAutomationExtension', False)
chrome_options.add_argument("--disable-blink-features=AutomationControlled")
chrome_options.add_argument("user-agent=Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/84.0.4147.125 Safari/537.36")


driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()),options=chrome_options)

stealth(driver,
    languages=["en-US", "en"],
    vendor="Google Inc.",
    platform="Win64",
    webgl_vendor="Intel Inc.",
    renderer="Intel Iris OpenGL Engine",
    fix_hairline=True,
    )
client = MongoClient("mongodb://roadto30.com:27017/")
mydatabase = client["MoviesAndTV"]
mycollection=mydatabase["Movies"]



class Movie:
    img=''
    url=''
    title=''
 
mlist=[]
i=1


URL="https://soap2day.cx/movielist?page="+str(i)

driver.get(URL)
print(driver.title)

element=driver.find_element(By.ID,"btnhome")
element.click()


time.sleep(3)
print(driver.title)



loopPages=True
while loopPages: 
    elements=driver.find_elements(By.CLASS_NAME,"col-lg-2")
    print(str(round((i/437)*100))+"%") 
    if len(elements)==0:
        print("-ELEMENTS LENGTH 0-")
        loopPages=False
    for element in elements:
        x=Movie()
        x.img=element.find_element(By.CSS_SELECTOR,'img').get_attribute('src')
        x.title=element.find_element(By.XPATH,'.//h5/a').text
        x.url=element.find_element(By.CSS_SELECTOR,'a').get_attribute('href')

        mycollection.replace_one({'Title':x.title},{'Title':x.title,'Image':x.img,"URL":x.url},upsert=True)

       
        #mlist.append(x);
        print(x.title)
    i+=1
    URL="https://soap2day.cx/movielist?page="+str(i)
    driver.get(URL)
    
 
# driver.get(x.url)
# WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CSS_SELECTOR, "video")))
        
# x.url=driver.find_element(By.TAG_NAME,'video').get_attribute('src')