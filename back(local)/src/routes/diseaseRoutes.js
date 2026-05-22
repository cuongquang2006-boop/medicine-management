const express = require("express");
const routes = express.Router();

const {
    getAllDiseases,
    createDisease,
    updateDisease,
    deleteDisease
} = require("../controllers/diseaseController");


routes.get("/",getAllDiseases);
routes.post("/",createDisease);
routes.put("/:id", updateDisease);
routes.delete("/:id", deleteDisease);

module.exports = routes;