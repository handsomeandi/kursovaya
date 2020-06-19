var password = document.getElementById("pwd");
var password_repeat = document.getElementById("pwd-repeat");

function validatePass(){
    if(password.value != password_repeat.value){
        password_repeat.setCustomValidity("Passwords Don't match");
    }else{
        password_repeat.setCustomValidity("");
    }
}

password.onchange = validatePass;
password_repeat.onkeyup = validatePass;

function refreshPage(){
    window.location.reload();
}