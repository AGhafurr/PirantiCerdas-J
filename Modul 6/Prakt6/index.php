<?php

$servername = "localhost";
$username = "root";
$password = "";
$dbname = "prakt6";  // Ganti sesuai dengan nama database Anda

if (isset($_GET["angka_sumbu_X"]) && isset($_GET["angka_sumbu_Y"]) && isset($_GET["kemiringan"]) && isset($_GET["indikator_buzzer"]) && isset($_GET["indikator_led"])) {
    $angka_sumbu_X = $_GET["angka_sumbu_X"];
    $angka_sumbu_Y = $_GET["angka_sumbu_Y"];
    $kemiringan = $_GET["kemiringan"];
    $indikator_buzzer = $_GET["indikator_buzzer"];
    $indikator_led = $_GET["indikator_led"];

    // Koneksi ke database
    $conn = new mysqli($servername, $username, $password, $dbname);

    // Cek koneksi
    if ($conn->connect_error) {
        die("Koneksi ke database gagal: " . $conn->connect_error);
    }

    // Query untuk memasukkan data ke dalam database
    $sql = "INSERT INTO `piranti` (`id_sensor_gerak`, `angka_sumbu_X`, `angka_sumbu_Y`, `kemiringan`, `indikator_buzzer`, `indikator_led`) VALUES (NULL, '$angka_sumbu_X', '$angka_sumbu_Y', '$kemiringan', '$indikator_buzzer', '$indikator_led')";

    if ($conn->query($sql) === TRUE) {
        echo "Data berhasil disimpan";
    } else {
        echo "Error: " . $sql . "<br>" . $conn->error;
    }

    // Tutup koneksi ke database
    $conn->close();
} else {
    echo "Data tidak lengkap";
}
?>
