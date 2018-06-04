// Length in ms of a dot
const INTERVAL = 100;

const form = document.querySelector("#translate-form");
const input = document.querySelector("#plaintext");
const textarea = document.querySelector("#ciphertext");
const playButton = document.querySelector("#play");

// Queries the server for morse translation
function translate(plaintext) {
  const url = "http://localhost:8080/api/translate";
  const req = new XMLHttpRequest();
  req.open("POST", url);
  req.setRequestHeader("Content-Type", "application/json");

  req.onload = function() {
    if(req.status == 200) {
      textarea.textContent = req.responseText;
    }
  }

  req.send(JSON.stringify({plaintext: plaintext.trim()}));
}

form.addEventListener('submit', (e) => {
  translate(input.value);
  e.preventDefault();
});

playButton.addEventListener("click", (e) => {
  if(textarea.textContent != '' && !textarea.textContent.includes("Data not received.")) {
    const counts = countMorseString(textarea.textContent);
    playMorseCounts(counts);
  }
});

// Converts morse string to list of numbers symbolizing lengths of time the
// audio will play and pause
function countMorseString(ciphertext) {
  const counts = [];
  const words = ciphertext.split('0000000');
  for(let w of words) {
    const letters = w.split('000');
    for(let l of letters) {
      const sequences = l.split('0');
      sequences.forEach((s) => counts.push(s.length * INTERVAL, INTERVAL));
      counts.pop();
      counts.push(3 * INTERVAL);
    }
    counts.pop();
    counts.push(7 * INTERVAL);
  }
  counts.pop();
  return counts;
}

// Plays the morse code string represented by list of counts
function playMorseCounts(counts) {
  const beep = new Audio('assets/audio/beep.wav');
  startBeep(beep, counts, 0);
}

function startBeep(beep, counts, index) {
  beep.currentTime = 0.1;
  beep.play();
  if(index == counts.length - 1) {
    setTimeout(() => beep.pause(), counts[index]);
  } else {
    setTimeout(stopBeep, counts[index], beep, counts, index + 1);
  }
}

function stopBeep(beep, counts, index) {
  if(index > counts.length - 1) return;
  beep.pause();
  setTimeout(startBeep, counts[index], beep, counts, index + 1);
}
