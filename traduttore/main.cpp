#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <regex>
#include "json.hpp"

using json = nlohmann::json;
using namespace std;

/* ===================== CLASSI ===================== */

class FileMultimediale {
    string id;
    string tipo;
    string src;
    string descrizione;

public:
    FileMultimediale(string i, string t, string s, string d)
        : id(i), tipo(t), src(s), descrizione(d) {}

    string getId() const { return id; }
    string getTipo() const { return tipo; }
    string getSrc() const { return src; }
    string getDescrizione() const { return descrizione; }
};

class Quiz {
    string id;
    string tipo;
    string domanda;
    vector<string> risposte;
    int risCorretta;

public:
    Quiz(string i, string t, string d, vector<string> r, int rc)
        : id(i), tipo(t), domanda(d), risposte(r), risCorretta(rc) {}

    string getId() const { return id; }
    string getTipo() const { return tipo; }
    string getDomanda() const { return domanda; }
    vector<string> getRisposte() const { return risposte; }
    int getRisCorretta() const { return risCorretta; }
};

class Lezione {
    int IDlezione;
    string titolo;
    int livello;
    int tempo;
    string imgLezione;
    string testo;
    vector<FileMultimediale> file;
    vector<Quiz> quiz;

public:
    Lezione(int id, string t, int l, int te, string img, string tx,
            vector<FileMultimediale> f, vector<Quiz> q)
        : IDlezione(id), titolo(t), livello(l), tempo(te),
          imgLezione(img), testo(tx), file(f), quiz(q) {}

    int getID() const { return IDlezione; }
    string getTitolo() const { return titolo; }
    int getLivello() const { return livello; }
    int getTempo() const { return tempo; }
    string getImg() const { return imgLezione; }
    string getTesto() const { return testo; }
    vector<FileMultimediale> getFile() const { return file; }
    vector<Quiz> getQuiz() const { return quiz; }
};

/* ===================== FUNZIONI ===================== */

// Funzione per mappare il numero del livello in testo (modificabile a piacere)
string livelloTesto(int livello) {
    switch(livello) {
        case 0: return "Base";
        case 1: return "Intermedio";
        case 2: return "Avanzato";
        default: return "Livello " + to_string(livello);
    }
}

// Parsing testo: <sb> → <h2>, testo prima → <p>, file multimediali subito dopo
string processaSezioni(const string& testo, const vector<FileMultimediale>& files) {
    string html;
    regex sb_regex("<sb>(.*?)</sb>");
    smatch match;
    string textCopy = testo;
    size_t lastPos = 0;

    while (regex_search(textCopy, match, sb_regex)) {
        string header = match[1].str();
        size_t matchPos = match.position();
        string pTesto = textCopy.substr(0, matchPos);
        if (!pTesto.empty()) html += "          <p>" + pTesto + "</p>\n";
        html += "          <h2>" + header + "</h2>\n";
        textCopy = match.suffix();
    }
    if (!textCopy.empty()) html += "          <p>" + textCopy + "</p>\n";

    // File multimediali subito dopo il testo
    for (const auto& f : files) {
        if (f.getTipo() == "immagine") {
            html += "          <img src=\"" + f.getSrc() + "\" alt=\"" + f.getDescrizione() + "\">\n";
        } else if (f.getTipo() == "video") {
            html += "          <video controls>\n"
                    "            <source src=\"" + f.getSrc() + "\" type=\"video/mp4\">\n"
                    "            Il tuo browser non supporta il video.\n"
                    "          </video>\n";
        }
    }

    return html;
}

/* ===================== MAIN ===================== */

int main() {
    ifstream input("lezioni.json");
    if (!input) {
        cerr << "Errore apertura lezioni.json\n";
        return 1;
    }

    json j;
    input >> j;

    vector<Lezione> lezioni;

    // Parsing JSON
    for (auto& l : j) {
        vector<FileMultimediale> files;
        for (auto& f : l["file"]) {
            files.emplace_back(f["id"], f["tipo"], f["src"], f["descrizione"]);
        }

        vector<Quiz> quiz;
        for (auto& q : l["quiz"]) {
            vector<string> ris;
            for (auto& r : q["risposte"]) ris.push_back(r);
            quiz.emplace_back(q["id"], q["tipo"], q["domanda"], ris, q["risCorretta"]);
        }

        lezioni.emplace_back(
            l["IDlezione"],
            l["titolo"],
            l["livello"],
            l["tempo"],
            l["imgLezione"],
            l["testo"],
            files,
            quiz
        );
    }

    // Generazione HTML per ciascuna lezione
    for (const auto& lezione : lezioni) {
        string nomeFile = "../html/Lezioni/lezione_" + to_string(lezione.getID()) + ".html";
        ofstream out(nomeFile); // <<-- Sovrascrive automaticamente se esiste
        if (!out) {
            cerr << "Errore creazione file HTML\n";
            continue;
        }

        out << "<!DOCTYPE html>\n"
               "<html lang=\"it\">\n"
               "<head>\n"
               "    <meta charset=\"UTF-8\">\n"
               "    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n"
               "    <title>" << lezione.getTitolo() << "</title>\n"
               "    <link rel=\"stylesheet\" href=\"../../css/style.css\">\n"
               "    <link rel=\"stylesheet\" href=\"../../css/lezioni.css\">\n"
               "</head>\n"
               "<body>\n"
               "    <!-- Header -->\n"
               "    <header class=\"topbar\">\n"
               "        <div class=\"logo\">Finencial</div>\n"
               "        <nav>\n"
               "            <a href=\"../nav-link/homepage.html\">Lessons</a>\n"
               "            <a href=\"../nav-link/feed.html\">Feed</a>\n"
               "            <a href=\"../nav-link/assistant.html\">Assistant</a>\n"
               "            <a href=\"../nav-link/account.html\">Account</a>\n"
               "        </nav>\n"
               "    </header>\n"
               "    <main>\n"
               "    <!-- Articolo -->\n"
               "    <div class=\"articolo\">\n"
               "        <div class=\"headerLezione\">\n"
               "            <h1>" << lezione.getTitolo() << "</h1>\n"
               "            <h3>Livello: " << livelloTesto(lezione.getLivello()) << "</h3>\n"
               "            <h3>Tempo: " << lezione.getTempo() << " minuti</h3>\n"
               "            <h3>Lezione numero: " << lezione.getID() << "</h3>\n"
               "            <img src=\"" << lezione.getImg() << "\" alt=\"immagine lezione\">\n"
               "        </div>\n"
               "        <div class=\"contenutoLezione\">\n";

        // Inserisco il testo diviso in sezioni + file
        out << processaSezioni(lezione.getTesto(), lezione.getFile());

        // Quiz
        if (!lezione.getQuiz().empty()) {
            out << "        <div class=\"domande\">\n"
                   "            <h2>Quiz</h2>\n"
                   "            <form id=\"quizForm\">\n";

            for (const auto& q : lezione.getQuiz()) {
                out << "            <div class=\"domanda\">\n"
                       "                <h3>" << q.getDomanda() << "</h3>\n";
                auto ris = q.getRisposte();
                for (size_t i = 0; i < ris.size(); ++i) {
                    out << "                    <label><input type=\"radio\" name=\"" << q.getId()
                        << "\" value=\"" << i << "\"> " << ris[i] << "</label><br>\n";
                }
                out << "            </div>\n";
            }

            out << "                <button type=\"submit\" onclick=\"checkQuiz()\">Invia Risposte</button>\n"
                   "            </form>\n"
                   "        </div>\n";
        }

        out << "        </div>\n"
               "    </main>\n"
               "    <script>\n"
               "        function checkQuiz() {\n"
               "            event.preventDefault();\n"
               "            let score = 0;\n"
               "            const totalQuestions = document.querySelectorAll('.domanda').length;\n"
               "            document.querySelectorAll('.domanda').forEach(q => {\n"
               "                const selected = q.querySelector('input:checked');\n"
               "                if (selected && parseInt(selected.value) === 0) score++;\n"
               "            });\n"
               "            alert(`Hai risposto correttamente a ${score} su ${totalQuestions} domande.`);\n"
               "            if (score === totalQuestions) window.location.href = \"../nav-link/homepage.html\";\n"
               "        }\n"
               "    </script>\n"
               "</body>\n"
               "</html>";

        cout << "Generato: " << nomeFile << "\n";
    }

    return 0;
}
