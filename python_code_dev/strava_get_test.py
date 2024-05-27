import requests
import json

# access_token="59b8e171fd8e2bb059ae59d030f4cfc462e13f2b"
# refresh="b65a670da38ee038c7ed7645c3cfcca7fa3552e9"

with open('secrets.json') as secrets_file:
    secrets = json.load(secrets_file)

access_token = secrets['access_token']
refresh_token = secrets['refresh_token']
client_secret = secrets['client_secret']
client_id = secrets['client_id']

headers = {
    'Authorization': f'Bearer {access_token}'
}


def check_token():
    response = requests.get('https://www.strava.com/api/v3/athlete', headers=headers)
    # Check if the response indicates a valid token
    if response.status_code == 200:
        print("Access token is valid.")
        return
    else: 
        response = requests.post('https://www.strava.com/oauth/token',
        data={
            'client_id': client_id,
            'client_secret': client_secret,
            'grant_type': 'refresh_token',
            'refresh_token': refresh_token
        })
        
    if response.status_code == 200:
        response_data = response.json()
        access_token = response_data['access_token']
        refresh_token = response_data['refresh_token']
        secrets['access_token'] = access_token
        secrets['refresh_token'] = refresh_token
        
        with open('secrets.json', 'w') as secrets_file:
            json.dump(secrets, secrets_file, indent=4)
    else:
        print(f"Failed to refresh access token: {response.status_code} {response.json()}")
        

# # Example request to get the authenticated user's profile
# 
def getAtheletedata():
    athlete = requests.get('https://www.strava.com/api/v3/athlete', headers=headers)
    athlete_response  = athlete.json()
    # print(athlete.json())
    athlete_id = athlete_response['id']
    print(athlete_id)
    athlete_stats = requests.get(f'https://www.strava.com/api/v3/athletes/{athlete_id}/stats', headers=headers)
    # print(athlete_stats.json())

def getActivitiesdata():
    params = {
    'page': 1,
    'per_page': 1
    }

    # Make the request to get the latest activities
    activityies_response = requests.get('https://www.strava.com/api/v3/athlete/activities', headers=headers,params=params)
    # print(activityies_response.json())
    activityies_response = activityies_response.json()
    for activity in activityies_response:
        print(f"Name: {activity['name']}, Distance: {activity['distance']}, Date: {activity['start_date']}")

check_token()
getAtheletedata()
getActivitiesdata()