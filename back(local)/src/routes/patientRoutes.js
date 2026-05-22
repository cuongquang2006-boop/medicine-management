const express = require("express");
const routes = express.Router();

const {
    getAllPatients,
    createPatient,
    updatePatient,
    deletePatient
} = require("../controllers/patientController");

routes.get("/", getAllPatients);
routes.post("/", createPatient);
routes.put("/:id", updatePatient);
routes.delete("/:id", deletePatient);

module.exports = routes;