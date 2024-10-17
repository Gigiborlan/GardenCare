import requests

url = "https://api.thingspeak.com/update"
api_key = "0AEKYH8ITL45PV1A"
temperatura = 25
umidade = 78
StatusLampada = 0
StatusBomba = 0

payload = {
    'api_key': api_key,
    'field1': temperatura,
    'field2': umidade,
    'field3': StatusLampada,
    'field4': StatusBomba
}

response = requests.get(url, params=payload)
print(response.status_code)