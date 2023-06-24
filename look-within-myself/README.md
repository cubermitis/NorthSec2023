# North Sec 2023 - Look Within Myself


From the discourse page we are given the following information:

![setup](../imgs/setup.png)

Based on the information given, we have to tinker with the image posted:

![myself-avatar](../src/myself-avatar.jpg)

Let's first check if there are embedded files within the image using the following command:

```bash
$ binwalk myself-avatar.jpg
```

![binwalk](../imgs/binwalk.png)

Okay so there's a zip file hidden, let's extract it using the following command:

```bash
$ binwalk --dd='.*' myself-avatar.jpg
```

![extract](../imgs/extract.png)

We now have the following [zip](../src/302D9.7z) file, it is password protected. From here we could attempt to brute force it with a tool but I was lucky and guessed the correct password to be `password`.

Inside the folder called `myself` we see a bunch of cat images and an interesting file called `myself.txt`

![folder](../imgs/folder.png)

We extract the flag from this file:

```
FLAG-43e1f21fd2741b2266eaf9c6cf93b46f62b73d7d9df0fa1e98611e6f64200815
```

Here was my favorite image:

![cat14](../src/myself/cat14.png)
