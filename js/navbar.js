function toggleMenu() {
    const menu = document.getElementById('mobileMenu');
    const hamburger = document.getElementById('hamburger');
    menu.classList.toggle('show');
    hamburger.classList.toggle('active');
}

function closeMenu() {
    document.getElementById('mobileMenu').classList.remove('show');
    document.getElementById('hamburger').classList.remove('active');
}

window.addEventListener('scroll', () => {
    const navbar = document.getElementById('navbar');
    if(window.scrollY>50){
        navbar.classList.add('scrolled');
    }else{
        navbar.classList.remove('scrolled');
    }
});

// Elementi
const topbar = document.querySelector('.topbar');
const hamburger = document.querySelector('.hamburger');
const navLinks = document.querySelector('.nav-links');

// 🔹 Riduce la navbar allo scroll
window.addEventListener('scroll', () => {
  if (window.scrollY > 50) {
    topbar.classList.add('scrolled');
  } else {
    topbar.classList.remove('scrolled');
  }
});

// 🔹 Toggle menu mobile
hamburger.addEventListener('click', () => {
  navLinks.classList.toggle('show');
  hamburger.classList.toggle('active');
});

// 🔹 Chiude il menu cliccando un link (mobile)
navLinks.querySelectorAll('a').forEach(link => {
  link.addEventListener('click', () => {
    navLinks.classList.remove('show');
    hamburger.classList.remove('active');
  });
});
