const express = require("express");
const dotenv = require("dotenv");
const cors = require("cors");

dotenv.config();
const pool = require("./config/db");

const patientRoutes = require("./routes/patientRoutes");

const clinicRoutes = require("./routes/clinicRoutes");

const diseaseRoutes = require("./routes/diseaseRoutes");

const medicineRoutes = require("./routes/medicineRoutes");

const prescriptionRoutes = require("./routes/prescriptionRoutes");

const userRoutes = require("./routes/userRoutes");

const dashboardRoutes = require("./routes/dashboardRoutes");

const app = express();

app.use(cors());
app.use(express.json());


app.get("/", async(req,res) => {
    try{
        const result = await pool.query("SELECT NOW()");

        res.status(200).json({
            success : true,
            message : "Database connected successfully",
            database_time : result.rows[0]
        });
    }
    catch(err){
        console.error("ERROR:", err);

        res.status(500).json({
            success : false,
            message : err.message
        });
    }
});


app.get("/ping", (req,res) => {
    console.log("PING HIT!");
    res.status(200).json({
        success : true,
        message : "PONG"
    })
}); 

app.use("/api/patients", patientRoutes);

app.use("/api/clinics", clinicRoutes);

app.use("/api/diseases", diseaseRoutes);

app.use("/api/medicines", medicineRoutes);

app.use("/api/prescriptions", prescriptionRoutes);

app.use("/api/users", userRoutes);

app.use("/api/dashboard", dashboardRoutes);


const PORT = process.env.PORT || 3000;

const server = app.listen(PORT, () => {
    console.log(`Server is running at http://127:0.0.1:${PORT}`);
});

process.on("SIGINT", ()=> {
    console.log("\n Closing server...");
    server.close(() => {
        console.log("Server closed!");
        process.exit(0);
    })
});
