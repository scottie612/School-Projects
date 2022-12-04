# -*- coding: utf-8 -*-
"""
Created on Fri Apr 30 21:33:59 2021

@author: Scottie
"""

import time

from selenium import webdriver

driver=webdriver.Chrome()

driver.get("https://www.bestbuy.com/site/nvidia-geforce-rtx-3070-8gb-gddr6-pci-express-4-0-graphics-card-dark-platinum-and-black/6429442.p?skuId=6429442")

Button=False

while not Button:
    addToCartButton=addButton=driver.find_element_by_class_name("add-to-cart-button")
  
    
    if("btn-disabled" in addToCartButton.get_attribute("class")):
        time.sleep(3)
        driver.refresh()
        addToCartButton=addButton=driver.find_element_by_class_name("add-to-cart-button")
    else:
        Button=True

addToCartButton.click()
driver.get("https://www.bestbuy.com/cart")
time.sleep(3)
checkout=addButton=driver.find_element_by_xpath('//button[text()="Checkout"]')
checkout.click()
