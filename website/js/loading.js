document.addEventListener("DOMContentLoaded", function() {
    setTimeout(function() {
        var element = document.getElementById("loading");
        if (element) {
            element.classList.add("fade-out");
            element.addEventListener('transitionend', function() {
                element.parentNode.removeChild(element);
            });
        }
    }, 1500);
});