const express = require("express");
const bodyparser = require("body-parser");
const ejs = require("ejs");

const app = express();

app.set('view engine', 'ejs');


app.use(bodyparser.urlencoded({
  extended: true
}));
app.use(express.static("public"));

app.get("/",function(req,res){
  res.render("index");
});

app.get("/signup",function(req,res){
  res.render("signup");
})

app.get("/login",function(req,res){
  res.render("login");
})

app.get("/SlotNo",function(req,res){
  res.render("SlotNo");
})

app.listen(3000,function(req,res){
  console.log("server started on port 3000");
});
