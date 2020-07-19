const express = require("express");
const bodyparser = require("body-parser");
const mysql = require('mysql')
const ejs = require("ejs");

const app = express();

app.set('view engine', 'ejs');


app.use(bodyparser.urlencoded({ extended: false }));
app.use(express.static("public"));

const db = mysql.createConnection({
  host     : 'localhost',
  user     : 'root',
  database : 'smartcarparking'
})

//connecting to database
db.connect((err) => {
  if(err)
    throw err
  console.log('MySQL database connected.')
})

//Starting page
app.get("/",(req,res) => {
  res.render("index");
  console.log('Index page opened.')
});

//Sign up page
app.get("/signup",(req,res) => {
  res.render("signup");
  console.log('Sign-up page opened.')
})

//Registering a user on db
app.post('/signup/register',(req,res) => {
  let user = {name: req.body.name, email: req.body.email, password: req.body.password, phnumber: req.body.phnumber, rc: req.body.rc}
  let sql = `INSERT INTO users SET ?`
  db.query(sql,user,(err,result) => {
    if(err)
      throw err;
    console.log('A user has been added.')
    res.redirect('/');
  })
})

//Login page
app.get('/login',(req,res) => {
  res.render('login')
  console.log('Login page has been opened.')
})

//Authenticating user
app.post('/login/auth',(req,res) => {
  let loginDetails = {email: req.body.email, password: req.body.password}
  let sql = `SELECT password FROM users WHERE email='${loginDetails.email}'`
  db.query(sql,(err,result) => {
    if(err)
      throw err;
    if( result[0].password == loginDetails.password){
      console.log('A user has been logged in.')
      res.redirect('/page1')
    }
  })
})

//Page1 page
app.get("/page1",(req,res) => {
  res.render("page1");
})

//Page to view available slots
app.get('/page1/seeavlslot',(req,res) => {
  let sql = 'SELECT * FROM slots'
  db.query(sql,(err,results) => {
    if(err)
      throw err;
    console.log('User viewing available slots.')
    res.render('seeAvlSlot',{ results: results })
  })
})

//Slot selection page
app.get("/selectSlotNo",(req,res) => {
  res.render("selectSlotNo");
  console.log('Select slot page opened')
})

//Slot update
app.post('/selectSlotNo/slotSelected',(req,res) => {
  let slotDetail = {slotno: req.body.slotno, status: 'OCCUPIED', phnumber: req.body.phnumber}
  let sql = `UPDATE slots SET status = '${slotDetail.status}', phnumber = ${slotDetail.phnumber} WHERE slotno = ${slotDetail.slotno}`
  db.query(sql,(err,result) => {
    if(err)
      throw err;
    console.log('Slots table updated.')
    res.redirect('/exitpage')
  })
})

//Exit slot page
app.get('/exitpage',(req,res) => {
  res.render('page2')
  console.log('Exit page has been opened.')
})

//Exiting the slot
app.post('/exitpage/exit',(req,res) => {
  let slot = { slotno: req.body.slotno, status: 'VACANT', phnumber: req.body.phnumber }
  let sql = `UPDATE slots SET status = '${slot.status}', phnumber = ${0} WHERE slotno = ${slot.slotno}`
  db.query(sql,(err,result)=>{
    if(err)
      throw err;
    console.log('User has left the slot.')
    res.redirect('/')
  })
})

const PORT = process.env.PORT || 3000

app.listen(PORT,() => console.log(`server started on port ${PORT}`));
