const validCodes = ["FINENCIALBETA261", "FINENCIALBETA262", "FINENCIALBETA263"];

const input = document.getElementById("betaCode");
const button = document.getElementById("enterBtn");
const errorMsg = document.getElementById("errorMsg");

button.addEventListener("click", () => {
    const enteredCode = input.value.trim();

    if (validCodes.includes(enteredCode)) {
        window.location.href = "html/nav-link/homepage.html";
    } else {
        errorMsg.textContent = "Codice beta non valido";
    }
});
