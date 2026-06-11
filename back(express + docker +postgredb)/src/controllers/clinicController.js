const pool = require("../config/db");

const getAllClinics = async(req,res) =>{
    
    try{

        const result = await pool.query(`

                SELECT
                    id,
                    name,
                    location,
                    description,
                    created_at

                FROM clinics

                ORDER BY id ASC
            `);

        res.status(200).json({
            success : true,
            total : result.rows.length,
            data : result.rows  
        });
    }

    catch(err){
        console.error("GET CLINIC ERROR: ", err);
        
        res.status(500).json({
            success : false,
            message : err.message
        });
    }
};


const createClinic = async(req,res)=>{

    try{
        const {
            name,
            location,
            description
        } = req.body;

        const result = await pool.query(`
                INSERT INTO clinics
                (name,location,description)

                VALUES 
                ($1,$2,$3)

                RETURNING *
            `,
            [
                name,
                location,
                description
            ]
        );

        res.status(201).json({
            success : true,
            message : "Clinic created",
            data : result.rows[0]
        });
    }

    catch(err){
        
        console.error("CREATE CLINIC ERROR:", err);
        
        res.status(500).json({
            success : false,
            message : err.message   
        });
    }
};

const updateClinic = async(req,res)=>{

    try{

        const id = req.params.id; // lay data tu id gan vao url

        const {
            name,
            location,
            description
        } = req.body;

        const result = await pool.query(`
                UPDATE clinics
                
                SET 
                    name = $1,
                    location = $2,
                    description = $3
                
                WHERE id = $4
                RETURNING *
            `,
            [
                name,
                location,
                description,
                id
            ]
        );

        if(result.rows.length === 0){
            return res.status(404).json({
                    success : false,
                    message : "Clinic not found"
        });}

        res.status(200).json({
            success : true,
            message : "Clinic updated",
            data : result.rows[0]
        });
    }
    catch(err){

        console.error("UPDATE CLINIC ERROR:", err);
        
        res.status(500).json({
            success : false,
            message : err.message
        });
    }
};


const deleteClinic = async(req,res)=>{

    try{

        const id = req.params.id;

        const result = await pool.query(

            `
            DELETE FROM clinics

            WHERE id = $1
            `,
            [id]
        );

        if(result.rowCount === 0)
        {
            return res.status(404).json({

                success:false,

                message:"Clinic not found"
            });
        }

        res.status(200).json({

            success:true,

            message:"Clinic deleted"
        });
    }

    catch(err){

        console.error("DELETE CLINIC ERROR:", err);

        res.status(500).json({

            success:false,

            message:err.message
        });
    }
};

module.exports =
{
    getAllClinics,
    createClinic,
    updateClinic,
    deleteClinic
};