# File encoder application

```
From: cp1251, koi8r, iso88595
To: utf-8
```

## How install and run

1. Download the code

```
git clone
```

2. Build

```
gcc main.c encoding/koi8r.c encoding/cp1251.c encoding/iso88595.c  -Wall -Wextra -Wpedantic -std=c11 -o converter
```

3. Run examples

```
Run ./converter examples/cp1251.txt cp1251
Run ./converter examples/koi8.txt koi8r
Run ./converter examples/iso-8859-5.txt iso88595 
```

4. Check created files

```
output_cp1251.txt
output_koi8r.txt
output_iso88595.txt
```

5. Done!