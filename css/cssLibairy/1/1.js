const shining_button = document.getElementById("shining_button2")
shining_button.addEventListener('click', function (e) {
    let x = e.offsetX
    let y = e.offsetY
    let ripples = document.createElement("span")
    ripples.style.left = x + 'px'
    ripples.style.top = y + 'px'
    this.appendChild(ripples)
    setTimeout(() => {
        ripples.remove();
    }, 1000)
})