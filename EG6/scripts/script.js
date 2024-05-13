const sprite_manual = document.getElementById('sprite1');
const sprite_auto = document.getElementById('sprite2');

let sprite_manual_frame = 0;
sprite_manual.addEventListener('click', function() {
    sprite_manual_frame = (sprite_manual_frame + 1) % 5;
    sprite_manual.style.backgroundPosition = `-${sprite_manual_frame * 32}px 0px`;
});

let sprite_auto_frame = 0;
function animateSprite() {
    sprite_auto_frame = (sprite_auto_frame + 1) % 5;
    sprite_auto.style.backgroundPosition = `-${sprite_auto_frame * 32}px -32px`;
}
setInterval(animateSprite, 1000);