----------

# 🏓 ft_ping — "Echoes" Meddle ; Released, _5 November 1971_ (1971-11-05) ;

Welcome to `ft_ping`, my school-sanctioned dive into the mysterious and emotionally detached world of ICMP packets. Inspired by the noble `ping(8)` utility and written entirely in C, this project seeks to answer a timeless question: "Is this host alive, or just ignoring me like everyone else?"

This isn’t just a clone — it’s a raw socket-powered, checksum-calculating, protocol-dissecting, TTL-respecting echo request renaissance.

> “If you throw a stone into a well and no sound reaches you; then the time to live has exceeded.”  
> — probably Confucius.

----------

## 📦 Project Structure

```
tiboitel-ft_ping/
├── includes/         # Headers that hold the universe together
├── srcs/             # The source of all problems (and some solutions)
├── Makefile          # Because compiling by hand is for suckers
└── README.md         # This is fine piece of literature 👌

```

----------

## 🔍 Features

-   🛰 IPv4 & IPv6 support — ping like it's 1996 or 2096.
    
-   🧠 ICMP & ICMPv6 packet crafting and parsing.
    
-   🕵️ Verbose mode (`-v`) for the packet sniffer in you. Whatever it means.
    
-   👻 Numeric-only mode (`-n`) — because DNS is for the weak.
    
-   ⏱ TTL tweaking (`-t`) to bring traceroute-esque enlightenment.
    
-   📉 RTT stats with min/avg/max/mdev — ping meets statistics class.
    

----------

## 🚀 Usage

```bash
./ft_ping [options] <destination>

```

### Options

Flag

Description

`-v`

Verbose output (because info = power)

`-n`

No DNS reverse resolution, just IPs, baby

`-t <ttl>`

Set the TTL (Time To Live)

`-6`

Force IPv6, for when you're feeling futuristic

`--version` or `-V`

Print version info, like a proper Unix tool

----------

## ⚙️ How It Works (Under the Hood, Where It Hurts)

> Warning: actual understanding may result in increased respect for ICMP headers and decreased respect for humanity.

### 🧱 main.c

Your typical `int main()` but with baggage. Parses flags, sets up the environment, and launches the eternal `ping_loop`. Handles signals like a stoic samurai on SIGINT.

### 🔄 ping.c

The engine room. Like Captain Kirk on caffeine, it loops through:

1.  Preparing the packet
    
2.  Sending it out into the abyss
    
3.  Waiting for a reply
    
4.  Parsing the reply and crying if it’s not ICMP_ECHOREPLY
    
5.  Measuring time with surgical precision (or best effort)
    
Handles IPv4 and IPv6 with elegance (read: large `if` statements and duplicated logic but with fancy pointer to functions).

### 📡 icmp.c

Forging raw ICMP/ICMPv6 packets with love, zeroes, and the power of bit-shifting. Parses responses and checks if the reply matches our sacred process ID.

> Checksums: because life isn’t fair, and neither are corrupted packets.

### 🧱 socket.c

Handles raw socket creation. Sets TTL, timeout, and other magic spells. Contains `send_icmp_packet()` and `receive_icmp_reply()`, which are as straightforward as they sound, until they segfault (they won’t. No heap, no troubles.).

### 🛠 utils.c

All the stuff we didn’t know where to put, like:

-   RTT calculations
-   Printing epic stats
-   ICMPv6 checksums that require a pseudo-header (because RFC says so, yeah, life is unfair)
-   Updating stats like a ping historian
    

----------

## 🧪 Example

```bash
./ft_ping -v -n -t 42 google.com
PING google.com (142.250.180.206) 56(84) bytes of data.
64 bytes from 142.250.180.206: icmp_req=1 ttl=113 time=11.23 ms
64 bytes from 142.250.180.206: icmp_req=2 ttl=113 time=10.98 ms
...

```

Then you Ctrl+C, and it whispers:

```
--- google.com ping statistics ---
5 packets transmitted, 5 received, 0% packet loss, time 5004ms
rtt min/avg/max/mdev = 10.94/11.06/11.23/0.11 ms

```

----------

## 🧯 Error Handling

We don't crash. We elegantly scream "Error" if:

-   You send non-integer arguments
-   Your TTL is something like `999`
-   You try to ping a cat instead of a host
-   You forget arguments altogether
-   You try to use ping as your LLM girlfriend
    

----------

## ✨ Fun Extras

-   Handles reverse DNS with `getnameinfo`, unless you're a cold-blooded `-n` user.
-   Clean Makefile with rules even your mom could love: `all`, `clean`, `fclean`, `re`
-   Setup your own TTL delay.
    

----------

## 🧪 Running Tests

Because peer-reviewers are people too:

```bash
make
./ft_ping 8.8.8.8

```

Try Ctrl+C to unleash the final RTT stats. Feels powerful, doesn’t it?

----------

## 📝 License

Licensed under the School of Life. You can use, modify, and break this code however you want — just don’t blame me when it starts replying with existential dread. 

----------

## 🧙‍♂️ Author

Written by [tiboitel](https://github.com/tiboitel), C wizard in training, certified `ping` philosopher, and probably the last human who builds Kernel in 3.9 on Debian 7 to make a project too old at 42.

----------

If you enjoyed this, wait ‘til you see my `traceroute` clone in the future — it cries when packets die.

See you Space Cowboy 🤠 🚀

