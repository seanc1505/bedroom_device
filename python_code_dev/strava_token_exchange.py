import requests
import json


with open('secrets.json') as secrets_file:
    secrets = json.load(secrets_file)

client_id = secrets['client_id']
client_secret = secrets['client_secret']
redirect_uri = secrets['redirect_uri']
auth_code = secrets['auth_code']


response = requests.post(
    url="https://www.strava.com/oauth/token",
    data={
        'client_id': client_id,
        'client_secret': client_secret,
        'code': auth_code,
        'grant_type': 'authorization_code'
    }
)


response_data = response.json()
access_token = response_data.get('access_token')
print(access_token)
refresh_token = response_data.get('refresh_token')
print(refresh_token)

secrets['access_token'] = access_token
secrets['refresh_token'] = refresh_token

with open('secrets.json', 'w') as secrets_file:
    json.dump(secrets, secrets_file, indent=4)
