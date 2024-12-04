import requests
import json
import time

# Replace with your Power BI REST API URL and dataset key
url = "https://api.powerbi.com/beta/{workspace_id}/datasets/{dataset_id}/rows?key={dataset_key}"

while True:
    # Fetch data from Google Sheets (you can use gspread or similar libraries)
    data = fetch_data_from_google_sheets()  # Implement this function

    # Prepare the payload
    payload = json.dumps({"rows": data})

    # Send data to Power BI
    response = requests.post(url, data=payload, headers={"Content-Type": "application/json"})
    
    if response.status_code == 200:
        print("Data pushed successfully")
    else:
        print("Error pushing data:", response.text)

    # Wait for 30 seconds before the next update
    time.sleep(30)
