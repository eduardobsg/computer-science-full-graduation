# This file is auto-generated from the current state of the database. Instead
# of editing this file, please use the migrations feature of Active Record to
# incrementally modify your database, and then regenerate this schema definition.
#
# Note that this schema.rb definition is the authoritative source for your
# database schema. If you need to create the application database on another
# system, you should be using db:schema:load, not running all the migrations
# from scratch. The latter is a flawed and unsustainable approach (the more migrations
# you'll amass, the slower it'll run and the greater likelihood for issues).
#
# It's strongly recommended to check this file into your version control system.

ActiveRecord::Schema.define(:version => 20120605024104) do

  create_table "emprestimos", :force => true do |t|
    t.integer  "pessoa_id"
    t.integer  "item_id"
    t.date     "dataDevolucao"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "item_tipos", :force => true do |t|
    t.string   "nome"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "items", :force => true do |t|
    t.string   "nome"
    t.text     "autor"
    t.string   "assunto"
    t.integer  "itemTipo_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "multas", :force => true do |t|
    t.integer  "pessoa_id"
    t.integer  "emprestimo_id"
    t.integer  "total"
    t.boolean  "emAberto"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "pessoa_tipos", :force => true do |t|
    t.string   "nome"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

  create_table "pessoas", :force => true do |t|
    t.string   "cpf"
    t.string   "senha"
    t.integer  "pessoaTipo_id"
    t.datetime "created_at"
    t.datetime "updated_at"
  end

end
