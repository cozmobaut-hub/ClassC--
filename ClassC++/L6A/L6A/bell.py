from pynput import keyboard
import os
import urllib.request
import subprocess
import sys

# Direct MP3 from a free SFX host (Taco Bell bong sound effect) [web:68]
SOUND_URL = "https://www.freesoundslibrary.com/wp-content/uploads/2021/06/taco-bell-sound-effect.mp3"
SOUND_FILE = "taco_bell_bong.mp3"
enabled = False

def ensure_ffplay():
    try:
        subprocess.run(
            ["ffplay", "-version"],
            stdout=subprocess.DEVNULL,
            stderr=subprocess.DEVNULL,
            check=True
        )
    except Exception:
        print("[TacoBell] ffplay (ffmpeg) not found. Install with: sudo apt install ffmpeg")
        sys.exit(1)

def ensure_sound():
    if not os.path.exists(SOUND_FILE):
        print("[TacoBell] Downloading sound from freesoundslibrary.com...")
        # Site provides a direct MP3 link for the Taco Bell bong sound [web:68]
        req = urllib.request.Request(
            SOUND_URL,
            headers={
                "User-Agent": (
                    "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
                    "AppleWebKit/537.36 (KHTML, like Gecko) "
                    "Chrome/122.0 Safari/537.36"
                )
            }
        )
        with urllib.request.urlopen(req) as resp, open(SOUND_FILE, "wb") as f:
            f.write(resp.read())
        print("[TacoBell] Downloaded", SOUND_FILE)

def play_sound():
    subprocess.Popen(
        ["ffplay", "-nodisp", "-autoexit", "-loglevel", "quiet", SOUND_FILE],
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )

def on_key_press(key):
    global enabled
    if enabled:
        play_sound()

def on_toggle():
    global enabled
    enabled = not enabled
    state = "ON" if enabled else "OFF"
    print(f"[TacoBell] Toggled {state}")

def on_esc_release(key):
    if key == keyboard.Key.esc:
        print("[TacoBell] Exiting")
        return False

def main():
    ensure_ffplay()
    ensure_sound()

    toggle_hotkey = keyboard.GlobalHotKeys({
        '<ctrl>+<alt>+t': on_toggle
    })
    toggle_hotkey.start()

    with keyboard.Listener(on_press=on_key_press,
                           on_release=on_esc_release) as listener:
        listener.join()

if __name__ == "__main__":
    main()