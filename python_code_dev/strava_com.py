import json
import requests

# Load secrets from secrets.json
with open('./python_code_dev/secrets.json', 'r') as f:
    secrets = json.load(f)

client_id = secrets['STRAVA_CLIENT_ID']
client_secret = secrets['STRAVA_CLIENT_SECRET']
refresh_token = secrets['STRAVA_REFRESH_TOKEN']
access_token = secrets['STRAVA_ACCESS_TOKEN']

# Strava API endpoints
# Get a new access token using the refresh token
auth_url = "https://www.strava.com/oauth/token"
payload = {
    'client_id': client_id,
    'client_secret': client_secret,
    'refresh_token': refresh_token,
    'grant_type': 'refresh_token'
}

# response = requests.post(auth_url, data=payload)
# response_data = response.json()
# print("response")
# print(response.text)
# if 'access_token' in response_data:
#     access_token = response_data['access_token']
#     # Update the secrets file with the new access token
#     secrets['STRAVA_ACCESS_TOKEN'] = access_token
#     print("yep")
#     with open('./python_code_dev/secrets.json', 'w') as f:
#         json.dump(secrets, f, indent=4)
# else:
#     print("Error getting access token:", response_data)
#     exit()
print(access_token)
# Fetch the latest activities
activities_url = "https://www.strava.com/api/v3/athlete"#/activities"
headers = {'Authorization': f'Authorization: Bearer {access_token}'}
params = {
    "per_page": 1,
    "page": 1
}
print("GET request to:", activities_url)
print("Headers:", headers)
print("Parameters:", params)

# Make the GET request
activities_response = requests.get(activities_url, headers=headers,params=params)

# Print the URL with parameters
print("Request URL:", activities_response.url)
print("hellpo")
# activities_response = requests.get(activities_url, headers=headers)

# Check if the response is successful
if activities_response.status_code != 200:
    print(f"Error fetching activities: {activities_response.status_code}")
    print(activities_response.text)
    exit()

try:
    activities = activities_response.json()
except json.JSONDecodeError as e:
    print("Error parsing JSON response:", e)
    print(activities_response.text)
    exit()
print(activities)
# # Check if activities is a list
# if not isinstance(activities, list):
#     print("Unexpected response format, expected a list of activities.")
#     print(activities)
#     exit()

# Print the latest activities
# for activity in activities:
#     try:
#         name = activity['name']
#         distance = activity['distance']
#         moving_time = activity['moving_time']
#         start_date = activity['start_date']
#         print(f"Name: {name}, Distance: {distance / 1000:.2f} km, Moving Time: {moving_time // 60} min, Start Date: {start_date}")
#     except KeyError as e:
#         print(f"Missing expected key in activity data: {e}")
#         print(activity)
