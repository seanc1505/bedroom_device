import requests
access_token = "0e427da6a3d82cfbe4662eb75f42691118ce0a59"

activities_url = "https://www.strava.com/api/v3/athlete/activities"
headers = {'Authorization': f'Authorization: Bearer {access_token}'}

activities_response = requests.get(activities_url, headers=headers)
print(activities_response)

print(activities_response.text)
# Check if the resp