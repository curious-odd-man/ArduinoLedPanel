var currentColor = null;


function setCurrentColor(event, color) {
    event.preventDefault();
    var match = color.match(/rgb\(([0-9]*),([0-9]*),([0-9]*)\)/);
    console.log('setCurrentColor:' + color);
    if (match) {
        currentColor = color;
        colorCanvas = document.getElementById('current-color-canvas');
        var colorctx = colorCanvas.getContext('2d');
        colorctx.fillStyle = currentColor;
        colorctx.fillRect(0, 0, colorCanvas.width, colorCanvas.height);
    }
}

