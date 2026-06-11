const express = require("express");
const routes = express.Router();

const {
    getAllClinics,
    createClinic,
    updateClinic,
    deleteClinic
} = require("../controllers/clinicController");

routes.get("/", getAllClinics);
routes.post("/", createClinic);
routes.put("/:id", updateClinic);
routes.delete("/id", deleteClinic);

module.exports = routes;