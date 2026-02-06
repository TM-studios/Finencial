/*********************************
 * DATI LEZIONI (può stare anche in un JSON esterno)
 *********************************/
const lezioni = [
    {
        "IDlezione": 1,
        "titolo": "Introduzione a Finencial",
        "livello": 0,
        "tempo": 10,
        "imgLezione": "../img/lezione1.jpg",
        "testo": "<sb>Cos'è Finencial?</sb>Finencial è una piattaforma educativa per imparare a gestire il denaro.<img1>Permette di seguire lezioni, fare quiz e monitorare i propri progressi.<vid1>",
        "file": [
            { "id": "img1", "tipo": "immagine", "src": "../lezione1/img/intro.jpg", "descrizione": "Logo Finencial" },
            { "id": "vid1", "tipo": "video", "src": "../lezione1/video/presentazione.mp4", "descrizione": "Video introduttivo" }
        ],
        "quiz": [
            { "id":"q1", "tipo":"multipla", "domanda":"Che tipo di piattaforma è Finencial?", "risposte":["Educativa","Social","Giochi","Musicale"], "risCorretta":0 }
        ]
    }
];

/*********************************
 * UTILS
 *********************************/
const params = new URLSearchParams(window.location.search);
const idLezione = parseInt(params.get("id")) || 1;
const lezione = lezioni.find(l => l.IDlezione === idLezione);

/*********************************
 * HEADER LEZIONE
 *********************************/
const header = document.querySelector(".headerLezione");
header.innerHTML = `
    <h1>${lezione.titolo}</h1>
    <h3>Livello: ${lezione.livello}</h3>
    <h3>Tempo: ${lezione.tempo} minuti</h3>
    <h3>Lezione numero: ${lezione.IDlezione}</h3>
    <img src="${lezione.imgLezione}" alt="${lezione.titolo}">
`;

/*********************************
 * CONTENUTO LEZIONE
 *********************************/
const contenuto = document.querySelector(".contenutoLezione");
let testoHTML = lezione.testo;

/* Titoli <sb> */
testoHTML = testoHTML.replace(/<sb>(.*?)<\/sb>/g, "<h2>$1</h2>");

/* Media */
lezione.file.forEach(f => {
    if (f.tipo === "immagine") {
        testoHTML = testoHTML.replace(
            `<${f.id}>`,
            `<img src="${f.src}" alt="${f.descrizione}">`
        );
    }

    if (f.tipo === "video") {
        testoHTML = testoHTML.replace(
            `<${f.id}>`,
            `<video controls>
                <source src="${f.src}" type="video/mp4">
            </video>`
        );
    }
});

contenuto.innerHTML = testoHTML;

/*********************************
 * QUIZ
 *********************************/
const quizBox = document.querySelector(".domande");

let quizHTML = `<h2>Quiz</h2><form id="quizForm">`;

lezione.quiz.forEach((q, index) => {
    quizHTML += `<div class="domanda"><h3>${q.domanda}</h3>`;

    q.risposte.forEach((r, i) => {
        quizHTML += `
            <label>
                <input type="radio" name="q${index}" value="${i}">
                ${r}
            </label><br>
        `;
    });

    quizHTML += `</div>`;
});

quizHTML += `<button type="submit">Invia Risposte</button></form>`;
quizBox.innerHTML = quizHTML;

/*********************************
 * CHECK QUIZ
 *********************************/
document.getElementById("quizForm").addEventListener("submit", e => {
    e.preventDefault();

    let score = 0;

    lezione.quiz.forEach((q, i) => {
        const risposta = document.querySelector(`input[name="q${i}"]:checked`);
        if (risposta && parseInt(risposta.value) === q.risCorretta) {
            score++;
        }
    });

    alert(`Hai risposto correttamente a ${score} su ${lezione.quiz.length}`);

    if (score === lezione.quiz.length) {
        window.location.href = "../nav-link/homepage.html";
    }
});
