
from pymongo import MongoClient,ASCENDING
from flask import Flask, jsonify, request, url_for, Response
from selenium import webdriver
from selenium_stealth import stealth
from selenium.webdriver.common.by import By
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException


class Dict(dict):
    def __add__(self, other):
        copy = self.copy()
        copy.update(other)
        return copy
    def __radd__(self, other):
        copy = other.copy()
        copy.update(self)
        return copy



app = Flask(__name__)


#=======================================GET VIDEO URL FROM MOVIE OBJECT URL=======================================
@app.route('/getURL/')
def getURL():
    URL = request.args.get('link')
    print(str(URL))
    driver.get(URL)

   
    WebDriverWait(driver, 10).until(EC.presence_of_element_located((By.CSS_SELECTOR, "video")))
        
    url=driver.find_element(By.TAG_NAME,'video').get_attribute('src')
    print(driver.title)
    json_file=jsonify({"url":url})
    json_file.headers.add('Access-Control-Allow-Origin', '*')
    return json_file



#=======================================GET LIST OF 30 RANDOM MOVIES=======================================
@app.route('/getMovieDatabase/')
def getMovieDatabase():
    client = MongoClient("mongodb://roadto30.com:27017/")
    mydatabase = client["MoviesAndTV"]
    mycollection=mydatabase["Movies"]
    
    j=1;
    mdict=Dict()
    data=mycollection.aggregate([{"$sample":{"size":30}}])
    for i in data:
        mdict=mdict+Dict({str(j):{"Title":i["Title"],'Image':i['Image'],'URL':i['URL']}})
        j+=1
        
    
    json_file=jsonify(mdict)
    json_file.headers.add('Access-Control-Allow-Origin', '*')
    print(json_file.data)
    return json_file


@app.route('/searchMovies/')
def searchMovies():
    query = request.args.get('query')
    client = MongoClient("mongodb://roadto30.com:27017/")
    mydatabase = client["MoviesAndTV"]
    mycollection=mydatabase["Movies"]
    
    mdict=Dict()
    j=1;
    #mycollection.create_index({"Title":"text"})
    data=mycollection.find({'Title': {"$regex":str(query),"$options":'i'}})
    for i in data:
        mdict=mdict+Dict({str(j):{"Title":i["Title"],'Image':i['Image'],'URL':i['URL']}})
        j+=1
    json_file=jsonify(mdict)
    json_file.headers.add('Access-Control-Allow-Origin', '*')
    print(json_file)
    return json_file
    
    

if __name__ == '__main__':
    
   
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
    driver.get("https://soap2day.cx/enter.html")
    print(driver.title)
    element=driver.find_element(By.ID,"btnhome")
    element.click()
   
app.run()


