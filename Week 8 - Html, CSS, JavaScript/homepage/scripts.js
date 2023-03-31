function navigate (id) {
    console.log(id)
    switch(id){
        case "btn_home":

            window.location.replace("./index.html");
            break;
        case "btn_cats":
            window.location.replace("./cats.html");
            break;
        case "btn_story":
            window.location.replace("./story.html");
            break;
        case "btn_food":
            window.location.replace("./food.html");
            break;
        }
}