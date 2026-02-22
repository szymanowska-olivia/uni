import asyncio
import aiohttp
import private as pv

async def dog():
    url = "https://dog.ceo/api/breeds/image/random"
    async with aiohttp.ClientSession() as session:
        print("Wysłano zapytanie do Dog API")
        async with session.get(url) as response:
            print("Wczytywanie odpowiedzi..")
            data = await response.json()
            print("URL obrazka psa")
            return data.get("message")

async def nasa():
    url = "https://api.nasa.gov/planetary/apod"
    params = {"api_key": pv.NASA_API_KEY}  
    async with aiohttp.ClientSession() as session:
        print("Wysłano zapytanie do NASA API")
        async with session.get(url, params=params) as response:
            print("Wczytywanie odpowiedzi..")
            data = await response.json()
            print("URL zdjęcia NASA APOD")
            return data.get("url") 

async def main():
    d, n = await asyncio.gather(dog(), nasa())
    print (d)
    print (n)

asyncio.run(main())

