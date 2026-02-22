import asyncio
import aiohttp
import private as pv
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import json

async def fred(date_start, date_end):
    url = "https://api.stlouisfed.org/fred/series/observations"
    params = {
        "series_id": "UNRATE",
        "api_key": pv.FRED_API_KEY,
        "file_type": "json",
        "frequency": "m",
        "observation_start": date_start,
        "observation_end": date_end
    }    
    async with aiohttp.ClientSession() as session:
        async with session.get(url, params=params) as response:
            data = await response.json()
            return data.get("observations") 

async def main():
    f, f2, f3 = await asyncio.gather(fred("2022-01-01","2023-01-01"), fred("2023-01-01","2024-01-01"), fred("2024-01-01","2025-01-01"))
    
    with open("fred_data.json", "w", encoding="utf-8") as fjson:
        json.dump({ "obs_2022_23": f, "obs_2023_24": f2, "obs_2024_25": f3}, fjson, indent=4)    
    
    obs = f
    obs2 = f2 
    obs3 = f3
    dates, dates2, dates3 = [], [], []
    values, values2, values3 = [], [], []


    for o in obs:
        dates.append(o["date"])
        values.append(float(o["value"]))   

    for o2 in obs2:
        dates2.append(o2["date"])
        values2.append(float(o2["value"]))     
    
    for o3 in obs3:
        dates3.append(o3["date"])
        values3.append(float(o3["value"]))     
   
        
    values4 = np.array(values + values2)

    a, b = np.polyfit(np.arange(len(values4)), values4, 1)

    x_pred = np.arange(len(values4), len(values4) + len(values3))
    y_pred = a * x_pred + b
    #print(y_pred)
    fig, (ax1, ax2, ax3) = plt.subplots(3,1)

    dates3_dt = pd.to_datetime(dates3)
    dates2_dt = pd.to_datetime(dates2)
    dates_dt = pd.to_datetime(dates)

    ax1.plot(dates_dt, values, marker='o', color='red', label='actual data')
    ax1.tick_params(axis='x', rotation=45)
    ax1.set_title('unemployment rate USA 2022-23')
    ax1.set_ylabel("Unemployment Rate (%)")
    ax1.set_xlabel("Month")

    ax2.plot(dates2_dt, values2, marker='o', color='blue', label='actual data')
    ax2.tick_params(axis='x', rotation=45)
    ax2.set_title('unemployment rate USA 2023-24')
    ax2.set_ylabel("Unemployment Rate (%)")
    ax2.set_xlabel("Month")

    ax3.plot(dates3_dt, values3, marker='o', color='green', label='actual data')
    ax3.plot(dates3_dt, y_pred, marker='x', color='pink', label='predicted data')
    ax3.tick_params(axis='x', rotation=45)    
    ax3.set_ylabel("Unemployment Rate (%)")
    ax3.set_xlabel("Month")
    ax3.set_title('unemployment rate USA 2024-25 prediction vs actual')
    
    ax3.legend()
    plt.tight_layout()
    plt.show()

asyncio.run(main())

