const pool = require("../config/db");



const getAllUsers = async(req,res) =>
{
    try
    {
        const result =
            await pool.query(

                `
                SELECT
                    id,
                    username,
                    full_name,
                    role,
                    created_at,
                    failed_attempts,
                    locked_until

                FROM users

                ORDER BY id ASC
                `
            );

        res.status(200).json({

            success:true,

            total:result.rows.length,

            data:result.rows
        });
    }

    catch(error)
    {
        console.error(
            "GET USERS ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const createUser = async(req,res) =>
{
    try
    {
        const
        {
            username,
            full_name,
            password,
            role

        } = req.body;

        const result =
            await pool.query(

                `
                INSERT INTO users
                (
                    username,
                    password_hash,
                    full_name,
                    role
                )

                VALUES
                (
                    $1,$2,$3,$4
                )

                RETURNING
                id,
                username,
                full_name,
                role,
                created_at
                `,

                [
                    username,
                    password,
                    full_name,
                    role
                ]
            );

        res.status(201).json({

            success:true,

            message:"User created",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "CREATE USER ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const updateUser = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        const
        {
            username,
            full_name,
            password,
            role

        } = req.body;

        const result =
            await pool.query(

                `
                UPDATE users

                SET
                    username = $1,
                    password_hash = $2,
                    full_name = $3,
                    role = $4

                WHERE id = $5

                RETURNING
                id,
                username,
                full_name,
                role,
                created_at
                `,

                [
                    username,
                    password,
                    full_name,
                    role,
                    id
                ]
            );

        res.status(200).json({

            success:true,

            message:"User updated",

            data:result.rows[0]
        });
    }

    catch(error)
    {
        console.error(
            "UPDATE USER ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


const deleteUser = async(req,res) =>
{
    try
    {
        const id =
            req.params.id;

        await pool.query(

            `
            DELETE FROM users

            WHERE id = $1
            `,

            [id]
        );

        res.status(200).json({

            success:true,

            message:"User deleted"
        });
    }

    catch(error)
    {
        console.error(
            "DELETE USER ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};

const loginUser = async(req,res) =>
{
    try
    {
        const
        {
            username,
            password

        } = req.body;

        const result =
            await pool.query(

                `
                SELECT *
                FROM users

                WHERE username = $1
                `,

                [username]
            );

        if(result.rows.length === 0)
        {
            return res.status(401).json({

                success:false,

                message:"Invalid username"
            });
        }

        const user =
            result.rows[0];

            //nếu vẫn đang bị lock và chưa hết tg lock
        if(user.locked_until && new Date(user.locked_until) > new Date())
        {
            //tính số mili giây còn lại
            const remainingMs = new Date(user.locked_until) - new Date();

            //đổi sang giây để gửi cho fe 
            const remainingSeconds = Math.ceil(remainingMs / 1000);

            //
            return res.status(403).json({

                success:false,
                message: "Account locked",
                remaining_seconds: remainingSeconds
            });
        }

        if(user.password_hash !== password)
        {
            let failedAttempts =
                user.failed_attempts + 1;

            let lockedUntil =
                null;

            if(failedAttempts >= 5)
            {
                lockedUntil =
                    new Date(
                        Date.now()
                        + 25 * 60 * 1000
                    );

                failedAttempts = 0;
            }

            await pool.query(

                `
                UPDATE users

                SET
                    failed_attempts = $1,
                    locked_until = $2

                WHERE id = $3
                `,

                [
                    failedAttempts,
                    lockedUntil,
                    user.id
                ]
            );

            return res.status(401).json({

                success:false,

                message:"Invalid password"
            });
        }

        await pool.query(

            `
            UPDATE users

            SET
                failed_attempts = 0,
                locked_until = NULL

            WHERE id = $1
            `,

            [user.id]
        );

        res.status(200).json({

            success:true,

            message:"Login successful",

            user:
            {
                id:user.id,

                username:user.username,

                full_name:user.full_name,

                role:user.role
            }
        });
    }

    catch(error)
    {
        console.error(
            "LOGIN ERROR:",
            error
            );

        res.status(500).json({

            success:false,

            message:error.message
        });
    }
};


module.exports =
{
    getAllUsers,
    createUser,
    updateUser,
    deleteUser,
    loginUser
};